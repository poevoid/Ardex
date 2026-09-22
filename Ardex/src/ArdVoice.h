/*
 * ArdVoice FX adaptation of Ignacio Vina's ArdVoice 0.1.
 * Original copyright (C) 2016 Ignacio Vina, Apache License 2.0.
 */
#ifndef ARDVOICE_FX_H
#define ARDVOICE_FX_H

#include <Arduino.h>
#include <ArduboyFX.h>

class ArdVoice {
public:
  ArdVoice();
  // Address relative to FX_DATA_PAGE. Call service() each loop iteration.
  void playVoiceFX(uint24_t address);
  void service();
  void stopVoice();
  bool isVoicePlaying();
};

#endif
