#define ABG_IMPLEMENTATION
#define ABG_SYNC_PARK_ROW
#define SPRITESU_IMPLEMENTATION
//#define OLED_SH1106  //for arduboy mini, set ABG_REFRESH_HZ TO 95
#define SPRITESU_OVERWRITE
#define SPRITESU_PLUSMASK
#define SPRITESU_FX
#include <ArduboyFX.h>
#include <ArdVoice.h>
#include "src/ArduboyG.h"
#include "src/SpritesU.hpp"
#include "fxdata/fxdata.h"
ArduboyG_Config<ABG_Mode::L4_Triplane> arduboy;
ArdVoice ardvoice;
#include "func.h"

void setup() {

  arduboy.begin();
  arduboy.startGray();
  FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);
  // FX::disableOLED();
  //FX::begin(FX_DATA_PAGE);
  // FX::setCursorRange(0,128);
  //FX::loadGameState(collection);
  //Wire.setClock(400000);
  // TWSR = 0b00000011;
  //TWBR = 1;
  //PRR0 &= ~_BV(PRTWI);
  //temp.begin();
  //temp.lowPowerMode(SHTC3_LOWPOW_MEAS_TFIRST_STRETCH);
  // readSoundData(pokemoncries, arrayBuffer, arraySize);  // Load a smaller portion (e.g., 128 bytes) initially
  
  arduboy.setCursor(0, 0);
}

void loop() {

  FX::enableOLED();

  arduboy.waitForNextPlane();
  FX::disableOLED();
  if (arduboy.needsUpdate()) {
    arduboy.pollButtons();
    update();
  }
  render();
}