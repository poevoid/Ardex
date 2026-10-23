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
uint16_t underflowTicks = 0;
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

inline void writeSample(uint8_t value) {
#if ARDEX_AUDIO_SPEAKER1
  OCR3A = value;
#elif defined(AB_ALTERNATE_WIRING)
  OCR4D = value;
#else
  OCR4A = value;
#endif
}

void silenceAndDisable() {
  TIMSK1 &= ~_BV(OCIE1A);
  TCCR1B = 0;
#if ARDEX_AUDIO_SPEAKER1
  TCCR3A = 0; // Disconnect OC3A: 50% PWM at idle is audible through an amp.
  TCCR3B = 0;
  SPEAKER_1_PORT &= ~_BV(SPEAKER_1_BIT);
#else
  TCCR4A = 0;
  TCCR4B = 0;
  TCCR4C = 0;
  SPEAKER_2_PORT &= ~_BV(SPEAKER_2_BIT);
#endif
  samplePosition = 0xFF;
  fadingOut = false;
}
}

ArdVoice::ArdVoice() {}

void ArdVoice::playVoiceFX(uint24_t address) {
  // Shut down the old voice before touching its queue or the FX chip.
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    silenceAndDisable();
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
  underflowTicks = 0;

  // Fill the ring before starting the timer; the ISR only reads RAM.
  service();
#if ARDEX_AUDIO_SPEAKER1
  pinMode(PIN_SPEAKER_1, OUTPUT);
  OCR3A = 127;
  TCCR3A = _BV(COM3A1) | _BV(WGM30);
  TCCR3B = _BV(WGM32) | _BV(CS30); // Timer3 fast 8-bit PWM, OC3A on pin 5.
#else
  pinMode(PIN_SPEAKER_2, OUTPUT);
  OCR4C = 0xFF;
#ifdef AB_ALTERNATE_WIRING
  TCCR4A = 0b00000010;
  OCR4D = 127;
  TCCR4C = 0b01000101; // OC4D on pin 6.
#else
  TCCR4A = 0b01000010;
  OCR4C = 0xFF;
  OCR4A = 127;          // OC4A on pin 13.
#endif
  TCCR4B = 0b00000001;
#endif

  // The encoder uses 8000 Hz samples. A dedicated compare interrupt avoids
  // the 62.5 kHz PWM overflow ISR that could starve the display/main loop.
  TCCR1A = 0;
  TCCR1B = _BV(WGM12) | _BV(CS10);
  OCR1A = F_CPU / 8000UL - 1;
  TCNT1 = 0;
  TIFR1 = _BV(OCF1A);
  TIMSK1 |= _BV(OCIE1A);
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

ISR(TIMER1_COMPA_vect) {
  if (samplePosition == 0xFF) return;

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
      // A blocked main loop must never leave the amplifier droning forever.
      writeSample(127);
      if (++underflowTicks >= 3200) silenceAndDisable(); // 400 ms at 8 kHz.
      return;
    }
    underflowTicks = 0;
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
  writeSample(soundBuffer[offset] = uint8_t(value));
  if (++samplePosition >= kSamplesPerFrame) samplePosition = 0;
}
