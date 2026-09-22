#include "Arduboy2.h"
#include "Arduino.h"
#include "Arduboy2Core.h"
#include "vars.h"

template<typename T>
//This animaton function takes a sprite and runs through all its frames, then starts over at frame 0
void animateSprite(T& structObj, uint8_t T::*cframe, uint8_t T::*framec, int T::*counter, uint8_t T::*wait) {
  if (structObj.*counter % (FRAME(structObj.*wait)) == 0) {
    if (structObj.*cframe < structObj.*framec) {
      structObj.*cframe += 1;
    } else {
      structObj.*cframe = 0;
    }
  }
  structObj.*counter += 1;
}


template<typename T>
//This animation function takes a sprite and runs trough all its frames in incremental order, then when reaching the final frame, in decremental order back to zero, ad infinitum
void animateFWB(T& structObj, uint8_t T::*cframe, uint8_t T::*framec, int T::*counter, uint8_t T::*wait, bool T::*inc) {
  if (structObj.*counter % (FRAME(structObj.*wait)) == 0) {
    if (structObj.*cframe == structObj.*framec) {
      structObj.*inc = false;
    }
    if (structObj.*cframe == 0) {
      structObj.*inc = true;
    }
    if (structObj.*inc) {
      if (structObj.*cframe < structObj.*framec) {
        structObj.*cframe += 1;
      }
    } else {
      if (structObj.*cframe > 0) {
        structObj.*cframe -= 1;
      }
    }
  }
  structObj.*counter += 1;
}
void entryBack() {
  ardvoice.stopVoice();
  entry.currententry = entry.currententry > 0 ? entry.currententry - 1 : maxEntryIndex;
  scrolly = 8;
}

void entryForward() {
  ardvoice.stopVoice();
  entry.currententry = entry.currententry < maxEntryIndex ? entry.currententry + 1 : 0;
  scrolly = 8;
}

void update() {
  switch (screen) {
    case Screen::Title:

      screen = Screen::Game;




      break;

    case Screen::Game:

      if (arduboy.justPressed(B_BUTTON)) {
        if (sprite.sprite == shinymonsters) {
          sprite.sprite = monsters;
        } else {
          sprite.sprite = shinymonsters;
        }
      }
      /* if (arduboy.justPressed(A_BUTTON)) {
        if (entry.textsprite == textentries){
          entry.textsprite = namesgray;
        }else {
          entry.textsprite = textentries;
        }
      }*/
      if (arduboy.justPressed(A_BUTTON)) {
        uint8_t addressBytes[3];
        FX::readDataBytes(cryIndex + uint24_t(entry.currententry) * 3,
                          addressBytes, sizeof(addressBytes));
        const uint24_t cryAddress = uint24_t(addressBytes[0]) |
              (uint24_t(addressBytes[1]) << 8) |
              (uint24_t(addressBytes[2]) << 16);
        ardvoice.playVoiceFX(cryAddress);
      }

      // animateSprite(sprite, &Sprite::currentframe, &Sprite::framecount, &Sprite::counter, &Sprite::framewait);
      //animateFWB(sprite, &Sprite::currentframe, &Sprite::framecount, &Sprite::counter, &Sprite::framewait, &Sprite::inc);
      if (arduboy.pressed(UP_BUTTON)) {
        if (scrolly < 32) {
          scrolly++;
        }
      }
      if (arduboy.pressed(DOWN_BUTTON)) {
        if (scrolly > -64) {
          scrolly--;
        }
      }
      /*if (arduboy.justPressed(LEFT_BUTTON) && entry.currententry > 0) {
        entry.currententry -= 1;
        scrolly =8;
      } else if (arduboy.justPressed(LEFT_BUTTON) && entry.currententry == 0) {
        entry.currententry = 250;
        scrolly =8;
      }
      if (arduboy.justPressed(RIGHT_BUTTON) && entry.currententry < 250) {
        entry.currententry += 1;
        scrolly =8;
      } else if (arduboy.justPressed(RIGHT_BUTTON) && entry.currententry == 250) {
        entry.currententry = 0;
        scrolly =8;
      }*/
      if (heldButton != 0) {
        if (arduboy.anyPressed(LEFT_BUTTON | RIGHT_BUTTON)) {
          if (repeatDelayCount != 0) {
            --repeatDelayCount;
          } else {
            if (heldButton == LEFT_BUTTON) {
              entryBack();
            } else {
              entryForward();
            }
          }
        } else {
          heldButton = 0;
        }
      } else {
        if (arduboy.justPressed(LEFT_BUTTON)) {
          heldButton = LEFT_BUTTON;
          repeatDelayCount = repeatDelay;
          entryBack();
        }
        if (arduboy.justPressed(RIGHT_BUTTON)) {
          heldButton = RIGHT_BUTTON;
          repeatDelayCount = repeatDelay;
          entryForward();
        }
      }

      break;


    case Screen::Gallery:

      break;


    case Screen::Gameover:

      if (arduboy.justPressed(A_BUTTON)) {
        screen = Screen::Title;
      }
      if (arduboy.justPressed(B_BUTTON)) {
        screen = Screen::Game;
      }
      break;
  }
}


void render() {
  uint16_t currentPlane = arduboy.currentPlane();

  switch (screen) {
    case Screen::Title:

      if (currentPlane <= 0) {  //dark gray
      }

      if (currentPlane <= 1) {  //gray
        arduboy.setCursor(0, 0);
        arduboy.println("ardex");
      }

      if (currentPlane <= 2) {  //white
      }
      break;

    case Screen::Game:
      arduboy.fillScreen(WHITE);

      SpritesU::drawPlusMaskFX(sprite.x, sprite.y, sprite.sprite, FRAME(entry.currententry));

      SpritesU::drawPlusMaskFX(entry.x + scrollx, entry.y + scrolly, entry.textsprite, FRAME(entry.currententry));



      if (currentPlane <= 0) {  //dark gray
      }

      if (currentPlane <= 1) {  //gray
        if (sprite.sprite == shinymonsters) {
          arduboy.println("Shiny!");
        }
      }

      if (currentPlane <= 2) {  //white
        arduboy.setCursor(0, 0);
        arduboy.print("No.");
        arduboy.print(entry.currententry + 1);
      }

      break;


    case Screen::Gallery:

      break;

    case Screen::Gameover:

      break;
  }
}
