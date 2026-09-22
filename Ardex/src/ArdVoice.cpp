/*
 * ArdVoice FX adaptation of Ignacio Vina's ArdVoice 0.1.
 * Original copyright (C) 2016 Ignacio Vina, Apache License 2.0.
 */
#include "ArdVoice.h"
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <string.h>

namespace {
constexpr uint8_t kSamplesPerFrame = 176;
constexpr uint8_t kRingSize = 8;  // One slot is reserved to distinguish full.
constexpr uint8_t kMaxCoeffs = 10;
constexpr uint8_t kFrameBytes = 2 + kMaxCoeffs;

uint8_t frames[kRingSize][kFrameBytes];
volatile uint8_t produced = 0;
volatile uint8_t consumed = 0;
uint24_t nextAddress = 0;
uint16_t queuedFrames = 0;
uint16_t totalFrames = 0;
volatile uint16_t remainingFrames = 0; // ISR owns this while timer is running.
uint8_t coeffCount = 0;

uint8_t soundBuffer[16];
int16_t coeffs[kMaxCoeffs];
int16_t gain = 0;
int16_t biasOffset = 0;
uint8_t pitchPeriod = 0;
volatile uint8_t samplePosition = 0xFF;
uint8_t sampleDivider = 1;
uint8_t fadeCounter = 0;
volatile bool fadingOut = false;

uint8_t fastRand8() {
  static uint8_t state[7] = {0x87, 0xdd, 0xdc, 0x10, 0x35, 0xbc, 0x5c};
  static uint16_t carry = 0x42;
  static uint8_t index = 0;
  const uint8_t x = state[index];
  const uint16_t value = uint16_t(x) * 0x3B + carry;
  carry = (value >> 8) + x;
  state[index] = uint8_t(value);
  if (++index == 7) index = 0;
  return state[index == 0 ? 6 : index - 1];
}

void silenceAndDisable() {
  OCR4A = 127;
#ifdef AB_ALTERNATE_WIRING
  OCR4D = 127;
#endif
  TIMSK4 = 0;
  samplePosition = 0xFF;
  fadingOut = false;
}
}

ArdVoice::ArdVoice() {}

void ArdVoice::playVoiceFX(uint24_t address) {
  // Shut down the old voice before touching its queue or the FX chip.
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    TIMSK4 = 0;
    samplePosition = 0xFF;
    OCR4A = 127;
#ifdef AB_ALTERNATE_WIRING
    OCR4D = 127;
#endif
  }
  produced = consumed = 0;
  queuedFrames = totalFrames = remainingFrames = 0;
  if (!address) return; // Zero in the index denotes a missing cry.

  uint8_t header[2];
  FX::readDataBytes(address, header, sizeof(header));
  totalFrames = uint16_t(header[0]) | (uint16_t(header[1] & 0x0F) << 8);
  coeffCount = header[1] >> 4;
  if (!totalFrames || coeffCount > kMaxCoeffs) return;
  remainingFrames = totalFrames;
  nextAddress = address + 2;
  fadingOut = false;
  fadeCounter = 32;
  samplePosition = 0;
  sampleDivider = 1;

  // Fill the ring before starting the timer; the ISR only reads RAM.
  service();
  TCCR4A = 0b01000010;
  TCCR4B = 0b00000001;
  OCR4C = 0xFF;
  OCR4A = 127;
#ifdef AB_ALTERNATE_WIRING
  TCCR4C = 0b01000101;
  OCR4D = 127;
#endif
  TIMSK4 = 0b00000100;
}

void ArdVoice::service() {
  if (samplePosition == 0xFF || fadingOut) return;
  const uint8_t bytesPerFrame = 2 + coeffCount;
  while (queuedFrames < totalFrames) {
    const uint8_t next = (produced + 1) & (kRingSize - 1);
    if (next == consumed) break;
    // FX::readDataBytes ends its SPI transaction. The ISR cannot touch FX.
    FX::readDataBytes(nextAddress, frames[produced], bytesPerFrame);
    nextAddress += bytesPerFrame;
    ++queuedFrames;
    asm volatile("" ::: "memory");
    produced = next; // Publish the complete frame with one byte store.
  }
}

void ArdVoice::stopVoice() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    if (samplePosition != 0xFF) {
      fadingOut = true;
      fadeCounter = 32;
    }
  }
}

bool ArdVoice::isVoicePlaying() {
  return samplePosition != 0xFF;
}

ISR(TIMER4_OVF_vect) {
  if (samplePosition == 0xFF) return;
  if (--sampleDivider) return;
  sampleDivider = 4;

  if (fadingOut && !fadeCounter) {
    silenceAndDisable();
    return;
  }
  if (samplePosition == 0 && !fadingOut) {
    if (!remainingFrames) {
      fadingOut = true;
      fadeCounter = 32;
      return;
    }
    if (consumed == produced) {
      // Wait for the main loop to refill the queue without reading SPI here.
      OCR4A = 127;
#ifdef AB_ALTERNATE_WIRING
      OCR4D = 127;
#endif
      return;
    }
    const uint8_t *frame = frames[consumed];
    const uint8_t pitch = frame[0];
    pitchPeriod = (pitch & 0x80) ? 0 : (pitch & 0x7F) + 20;
    gain = frame[1];
    biasOffset = 64;
    for (uint8_t i = 0; i < coeffCount; ++i) {
      const uint8_t c = frame[i + 2];
      const int8_t denominator = int8_t(c & 0x7F) - 64;
      coeffs[i] = (c & 0x80) ? (denominator ? 4096 / denominator : 0)
                             : int16_t(c) - 64;
      biasOffset += coeffs[i];
    }
    biasOffset *= 127;
    memset(soundBuffer, 127, sizeof(soundBuffer));
    consumed = (consumed + 1) & (kRingSize - 1);
    --remainingFrames;
  }

  const uint8_t offset = samplePosition & 0x0F;
  int16_t value = fadingOut ? 0
    : pitchPeriod ? ((samplePosition % pitchPeriod) ? 0 : gain * 127)
                  : gain * (int16_t(fastRand8()) - 127);
  for (uint8_t i = 0; i < coeffCount; ++i)
    value -= coeffs[i] * soundBuffer[(offset - i - 1) & 0x0F];
  value = (value + biasOffset) >> 6;
  value = value < 0 ? 0 : value > 255 ? 255 : value;
  if (fadeCounter) {
    value = fadingOut ? 127 + ((value - 127) * fadeCounter) / 32
                      : 127 + ((value - 127) * (32 - fadeCounter)) / 32;
    --fadeCounter;
  }
  OCR4A = soundBuffer[offset] = uint8_t(value);
#ifdef AB_ALTERNATE_WIRING
  OCR4D = soundBuffer[offset];
#endif
  if (++samplePosition >= kSamplesPerFrame) samplePosition = 0;
}
