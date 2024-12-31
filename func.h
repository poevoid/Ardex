#include "Arduboy2.h"
#include "Arduino.h"
#include "Arduboy2Core.h"
#include "vars.h"
/*
void handlecries() {
  if (entry.currententry == 0) {
    entry.cry = p01;
  }
  if (entry.currententry == 1) {
    entry.cry = p02;
  }
  if (entry.currententry == 2) {
    entry.cry = p03;
  }
  if (entry.currententry == 3) {
    entry.cry = p04;
  }
  if (entry.currententry == 4) {
    entry.cry = p05;
  }
  if (entry.currententry == 5) {
    entry.cry = p06;
  }
  if (entry.currententry == 6) {
    entry.cry = p07;
  }
  if (entry.currententry == 7) {
    entry.cry = p08;
  }
  if (entry.currententry == 8) {
    entry.cry = p09;
  }
  if (entry.currententry == 9) {
    entry.cry = p10;
  }
  if (entry.currententry == 10) {
    entry.cry = p11;
  }
  if (entry.currententry == 11) {
    entry.cry = p12;
  }
  if (entry.currententry == 12) {
    entry.cry = p13;
  }
  if (entry.currententry == 13) {
    entry.cry = p14;
  }
  if (entry.currententry == 14) {
    entry.cry = p15;
  }
  if (entry.currententry == 15) {
    entry.cry = p16;
  }
  if (entry.currententry == 16) {
    entry.cry = p17;
  }
  if (entry.currententry == 17) {
    entry.cry = p18;
  }
  if (entry.currententry == 18) {
    entry.cry = p19;
  }
  if (entry.currententry == 19) {
    entry.cry = p20;
  }
  if (entry.currententry == 20) {
    entry.cry = p21;
  }
  if (entry.currententry == 21) {
    entry.cry = p22;
  }
  if (entry.currententry == 22) {
    entry.cry = p23;
  }
  if (entry.currententry == 23) {
    entry.cry = p24;
  }
  if (entry.currententry == 24) {
    entry.cry = p25;
  }
  if (entry.currententry == 25) {
    entry.cry = p26;
  }
  if (entry.currententry == 26) {
    entry.cry = p27;
  }
  if (entry.currententry == 27) {
    entry.cry = p28;
  }
  if (entry.currententry == 28) {
    entry.cry = p29;
  }
  if (entry.currententry == 29) {
    entry.cry = p30;
  }
  if (entry.currententry == 30) {
    entry.cry = p31;
  }
  if (entry.currententry == 31) {
    entry.cry = p32;
  }
  if (entry.currententry == 32) {
    entry.cry = p33;
  }
  if (entry.currententry == 33) {
    entry.cry = p34;
  }
  if (entry.currententry == 34) {
    entry.cry = p35;
  }
  if (entry.currententry == 35) {
    entry.cry = p36;
  }
  if (entry.currententry == 36) {
    entry.cry = p37;
  }
  if (entry.currententry == 37) {
    entry.cry = p38;
  }
  if (entry.currententry == 38) {
    entry.cry = p39;
  }
  if (entry.currententry == 39) {
    entry.cry = p40;
  }
  if (entry.currententry == 40) {
    entry.cry = p41;
  }
  if (entry.currententry == 41) {
    entry.cry = p42;
  }
  if (entry.currententry == 42) {
    entry.cry = p43;
  }
  if (entry.currententry == 43) {
    entry.cry = p44;
  }
  if (entry.currententry == 44) {
    entry.cry = p45;
  }
  if (entry.currententry == 45) {
    entry.cry = p46;
  }
  if (entry.currententry == 46) {
    entry.cry = p47;
  }
  if (entry.currententry == 47) {
    entry.cry = p48;
  }
  if (entry.currententry == 48) {
    entry.cry = p49;
  }
  if (entry.currententry == 49) {
    entry.cry = p50;
  }
  if (entry.currententry == 50) {
    entry.cry = p51;
  }
  if (entry.currententry == 51) {
    entry.cry = p52;
  }
  if (entry.currententry == 52) {
    entry.cry = p53;
  }
  if (entry.currententry == 53) {
    entry.cry = p54;
  }
  if (entry.currententry == 54) {
    entry.cry = p55;
  }
  if (entry.currententry == 55) {
    entry.cry = p56;
  }
  if (entry.currententry == 56) {
    entry.cry = p57;
  }
  if (entry.currententry == 57) {
    entry.cry = p58;
  }
  if (entry.currententry == 58) {
    entry.cry = p59;
  }
  if (entry.currententry == 59) {
    entry.cry = p60;
  }
  if (entry.currententry == 60) {
    entry.cry = p61;
  }
  if (entry.currententry == 61) {
    entry.cry = p62;
  }
  if (entry.currententry == 62) {
    entry.cry = p63;
  }
  if (entry.currententry == 63) {
    entry.cry = p64;
  }
  if (entry.currententry == 64) {
    entry.cry = p65;
  }
  if (entry.currententry == 65) {
    entry.cry = p66;
  }
  if (entry.currententry == 66) {
    entry.cry = p67;
  }
  if (entry.currententry == 67) {
    entry.cry = p68;
  }
  if (entry.currententry == 68) {
    entry.cry = p69;
  }
  if (entry.currententry == 69) {
    entry.cry = p70;
  }
  if (entry.currententry == 70) {
    entry.cry = p71;
  }
  if (entry.currententry == 71) {
    entry.cry = p72;
  }
  if (entry.currententry == 72) {
    entry.cry = p73;
  }
  if (entry.currententry == 73) {
    entry.cry = p74;
  }
  if (entry.currententry == 74) {
    entry.cry = p75;
  }
  if (entry.currententry == 75) {
    entry.cry = p76;
  }
  if (entry.currententry == 76) {
    entry.cry = p77;
  }
  if (entry.currententry == 77) {
    entry.cry = p78;
  }
  if (entry.currententry == 78) {
    entry.cry = p79;
  }
  if (entry.currententry == 79) {
    entry.cry = p80;
  }
  if (entry.currententry == 80) {
    entry.cry = p81;
  }
  if (entry.currententry == 81) {
    entry.cry = p82;
  }
  if (entry.currententry == 82) {
    entry.cry = p83;
  }
  if (entry.currententry == 83) {
    entry.cry = p84;
  }
  if (entry.currententry == 84) {
    entry.cry = p85;
  }
  if (entry.currententry == 85) {
    entry.cry = p86;
  }
  if (entry.currententry == 86) {
    entry.cry = p87;
  }
  if (entry.currententry == 87) {
    entry.cry = p88;
  }
  if (entry.currententry == 88) {
    entry.cry = p89;
  }
  if (entry.currententry == 89) {
    entry.cry = p90;
  }
  if (entry.currententry == 90) {
    entry.cry = p91;
  }
  if (entry.currententry == 91) {
    entry.cry = p92;
  }
  if (entry.currententry == 92) {
    entry.cry = p93;
  }
  if (entry.currententry == 93) {
    entry.cry = p94;
  }
  if (entry.currententry == 94) {
    entry.cry = p95;
  }
  if (entry.currententry == 95) {
    entry.cry = p96;
  }
  if (entry.currententry == 96) {
    entry.cry = p97;
  }
  if (entry.currententry == 97) {
    entry.cry = p98;
  }
  if (entry.currententry == 98) {
    entry.cry = p99;
  }
  if (entry.currententry == 99) {
    entry.cry = p100;
  }
  if (entry.currententry == 100) {
    entry.cry = p101;
  }
  if (entry.currententry == 101) {
    entry.cry = p102;
  }
  if (entry.currententry == 102) {
    entry.cry = p103;
  }
  if (entry.currententry == 103) {
    entry.cry = p104;
  }
  if (entry.currententry == 104) {
    entry.cry = p105;
  }
  if (entry.currententry == 105) {
    entry.cry = p106;
  }
  if (entry.currententry == 106) {
    entry.cry = p107;
  }
  if (entry.currententry == 107) {
    entry.cry = p108;
  }
  if (entry.currententry == 108) {
    entry.cry = p109;
  }
  if (entry.currententry == 109) {
    entry.cry = p110;
  }
  if (entry.currententry == 110) {
    entry.cry = p111;
  }
  if (entry.currententry == 111) {
    entry.cry = p112;
  }
  if (entry.currententry == 112) {
    entry.cry = p113;
  }
  if (entry.currententry == 113) {
    entry.cry = p114;
  }
  if (entry.currententry == 114) {
    entry.cry = p115;
  }
  if (entry.currententry == 115) {
    entry.cry = p116;
  }
  if (entry.currententry == 116) {
    entry.cry = p117;
  }
  if (entry.currententry == 117) {
    entry.cry = p118;
  }
  if (entry.currententry == 118) {
    entry.cry = p119;
  }
  if (entry.currententry == 119) {
    entry.cry = p120;
  }
  if (entry.currententry == 120) {
    entry.cry = p121;
  }
  if (entry.currententry == 121) {
    entry.cry = p122;
  }
  if (entry.currententry == 122) {
    entry.cry = p123;
  }
  if (entry.currententry == 123) {
    entry.cry = p124;
  }
  if (entry.currententry == 124) {
    entry.cry = p125;
  }
  if (entry.currententry == 125) {
    entry.cry = p126;
  }
  if (entry.currententry == 126) {
    entry.cry = p127;
  }
  if (entry.currententry == 127) {
    entry.cry = p128;
  }
  if (entry.currententry == 128) {
    entry.cry = p129;
  }
  if (entry.currententry == 129) {
    entry.cry = p130;
  }
  if (entry.currententry == 130) {
    entry.cry = p131;
  }
  if (entry.currententry == 131) {
    entry.cry = p132;
  }
  if (entry.currententry == 132) {
    entry.cry = p133;
  }
  if (entry.currententry == 133) {
    entry.cry = p134;
  }
  if (entry.currententry == 134) {
    entry.cry = p135;
  }
  if (entry.currententry == 135) {
    entry.cry = p136;
  }
  if (entry.currententry == 136) {
    entry.cry = p137;
  }
  if (entry.currententry == 137) {
    entry.cry = p138;
  }
  if (entry.currententry == 138) {
    entry.cry = p139;
  }
  if (entry.currententry == 139) {
    entry.cry = p140;
  }
  if (entry.currententry == 140) {
    entry.cry = p141;
  }
  if (entry.currententry == 141) {
    entry.cry = p142;
  }
  if (entry.currententry == 142) {
    entry.cry = p143;
  }
  if (entry.currententry == 143) {
    entry.cry = p144;
  }
  if (entry.currententry == 144) {
    entry.cry = p145;
  }
  if (entry.currententry == 145) {
    entry.cry = p146;
  }
  if (entry.currententry == 146) {
    entry.cry = p147;
  }
  if (entry.currententry == 147) {
    entry.cry = p148;
  }
  if (entry.currententry == 148) {
    entry.cry = p149;
  }
  if (entry.currententry == 149) {
    entry.cry = p150;
  }
  if (entry.currententry == 150) {
    entry.cry = p151;
  }
  if (entry.currententry == 151) {
    entry.cry = p152;
  }
  if (entry.currententry == 152) {
    entry.cry = p153;
  }
  if (entry.currententry == 153) {
    entry.cry = p154;
  }
  if (entry.currententry == 154) {
    entry.cry = p155;
  }
  if (entry.currententry == 155) {
    entry.cry = p156;
  }
  if (entry.currententry == 156) {
    entry.cry = p157;
  }
  if (entry.currententry == 157) {
    entry.cry = p158;
  }
  if (entry.currententry == 158) {
    entry.cry = p159;
  }
  if (entry.currententry == 159) {
    entry.cry = p160;
  }
  if (entry.currententry == 160) {
    entry.cry = p161;
  }
  if (entry.currententry == 161) {
    entry.cry = p162;
  }
  if (entry.currententry == 162) {
    entry.cry = p163;
  }
  if (entry.currententry == 163) {
    entry.cry = p164;
  }
  if (entry.currententry == 164) {
    entry.cry = p165;
  }
  if (entry.currententry == 165) {
    entry.cry = p166;
  }
  if (entry.currententry == 166) {
    entry.cry = p167;
  }
  if (entry.currententry == 167) {
    entry.cry = p168;
  }
  if (entry.currententry == 168) {
    entry.cry = p169;
  }
  if (entry.currententry == 169) {
    entry.cry = p170;
  }
  if (entry.currententry == 170) {
    entry.cry = p171;
  }
  if (entry.currententry == 171) {
    entry.cry = p172;
  }
  if (entry.currententry == 172) {
    entry.cry = p173;
  }
  if (entry.currententry == 173) {
    entry.cry = p174;
  }
  if (entry.currententry == 174) {
    entry.cry = p175;
  }
  if (entry.currententry == 175) {
    entry.cry = p176;
  }
  if (entry.currententry == 176) {
    entry.cry = p177;
  }
  if (entry.currententry == 177) {
    entry.cry = p178;
  }
  if (entry.currententry == 178) {
    entry.cry = p179;
  }
  if (entry.currententry == 179) {
    entry.cry = p180;
  }
  if (entry.currententry == 180) {
    entry.cry = p181;
  }
  if (entry.currententry == 181) {
    entry.cry = p182;
  }
  if (entry.currententry == 182) {
    entry.cry = p183;
  }
  if (entry.currententry == 183) {
    entry.cry = p184;
  }
  if (entry.currententry == 184) {
    entry.cry = p185;
  }
  if (entry.currententry == 185) {
    entry.cry = p186;
  }
  if (entry.currententry == 186) {
    entry.cry = p187;
  }
  if (entry.currententry == 187) {
    entry.cry = p188;
  }
  if (entry.currententry == 188) {
    entry.cry = p189;
  }
  if (entry.currententry == 189) {
    entry.cry = p190;
  }
  if (entry.currententry == 190) {
    entry.cry = p191;
  }
  if (entry.currententry == 191) {
    entry.cry = p192;
  }
  if (entry.currententry == 192) {
    entry.cry = p193;
  }
  if (entry.currententry == 193) {
    entry.cry = p194;
  }
  if (entry.currententry == 194) {
    entry.cry = p195;
  }
  if (entry.currententry == 195) {
    entry.cry = p196;
  }
  if (entry.currententry == 196) {
    entry.cry = p197;
  }
  if (entry.currententry == 197) {
    entry.cry = p198;
  }
  if (entry.currententry == 198) {
    entry.cry = p199;
  }
  if (entry.currententry == 199) {
    entry.cry = p200;
  }
  if (entry.currententry == 200) {
    entry.cry = p201;
  }
  if (entry.currententry == 201) {
    entry.cry = p202;
  }
  if (entry.currententry == 202) {
    entry.cry = p203;
  }
  if (entry.currententry == 203) {
    entry.cry = p204;
  }
  if (entry.currententry == 204) {
    entry.cry = p205;
  }
  if (entry.currententry == 205) {
    entry.cry = p206;
  }
  if (entry.currententry == 206) {
    entry.cry = p207;
  }
  if (entry.currententry == 207) {
    entry.cry = p208;
  }
  if (entry.currententry == 208) {
    entry.cry = p209;
  }
  if (entry.currententry == 209) {
    entry.cry = p210;
  }
  if (entry.currententry == 210) {
    entry.cry = p211;
  }
  if (entry.currententry == 211) {
    entry.cry = p212;
  }
  if (entry.currententry == 212) {
    entry.cry = p213;
  }
  if (entry.currententry == 213) {
    entry.cry = p214;
  }
  if (entry.currententry == 214) {
    entry.cry = p215;
  }
  if (entry.currententry == 215) {
    entry.cry = p216;
  }
  if (entry.currententry == 216) {
    entry.cry = p217;
  }
  if (entry.currententry == 217) {
    entry.cry = p218;
  }
  if (entry.currententry == 218) {
    entry.cry = p219;
  }
  if (entry.currententry == 219) {
    entry.cry = p220;
  }
  if (entry.currententry == 220) {
    entry.cry = p221;
  }
  if (entry.currententry == 221) {
    entry.cry = p222;
  }
  if (entry.currententry == 222) {
    entry.cry = p223;
  }
  if (entry.currententry == 223) {
    entry.cry = p224;
  }
  if (entry.currententry == 224) {
    entry.cry = p225;
  }
  if (entry.currententry == 225) {
    entry.cry = p226;
  }
  if (entry.currententry == 226) {
    entry.cry = p227;
  }
  if (entry.currententry == 227) {
    entry.cry = p228;
  }
  if (entry.currententry == 228) {
    entry.cry = p229;
  }
  if (entry.currententry == 229) {
    entry.cry = p230;
  }
  if (entry.currententry == 230) {
    entry.cry = p231;
  }
  if (entry.currententry == 231) {
    entry.cry = p232;
  }
  if (entry.currententry == 232) {
    entry.cry = p233;
  }
  if (entry.currententry == 233) {
    entry.cry = p234;
  }
  if (entry.currententry == 234) {
    entry.cry = p235;
  }
  if (entry.currententry == 235) {
    entry.cry = p236;
  }
  if (entry.currententry == 236) {
    entry.cry = p237;
  }
  if (entry.currententry == 237) {
    entry.cry = p238;
  }
  if (entry.currententry == 238) {
    entry.cry = p239;
  }
  if (entry.currententry == 239) {
    entry.cry = p240;
  }
  if (entry.currententry == 240) {
    entry.cry = p241;
  }
  if (entry.currententry == 241) {
    entry.cry = p242;
  }
  if (entry.currententry == 242) {
    entry.cry = p243;
  }
  if (entry.currententry == 243) {
    entry.cry = p244;
  }
  if (entry.currententry == 244) {
    entry.cry = p245;
  }
  if (entry.currententry == 245) {
    entry.cry = p246;
  }
  if (entry.currententry == 246) {
    entry.cry = p247;
  }
  if (entry.currententry == 247) {
    entry.cry = p248;
  }
  if (entry.currententry == 248) {
    entry.cry = p249;
  }
  if (entry.currententry == 249) {
    entry.cry = p250;
  }
  if (entry.currententry == 250) {
    entry.cry = p251;
  }
}*/ //old code, probably will delete
void readSoundData(uint24_t address, uint16_t* buffer, uint8_t bufferSize) {
  FX::seekData(address);  // Use the address directly

  // Read the array data from FX into arrayBuffer
  for (uint8_t i = 0; i < bufferSize; i++) {
    uint16_t value;
    if (i == bufferSize - 1) {
      // Use readPendingLastUInt16() for the last element
      value = FX::readPendingLastUInt16();
    } else {
      // Use readPendingUInt16() for intermediate elements
      value = FX::readPendingUInt16();
    }

    // Store the value in the buffer
    buffer[i] = value;
  }
}

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
  entry.currententry = entry.currententry > 0 ? entry.currententry - 1 : maxEntryIndex;
  scrolly = 8;
}

void entryForward() {
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
     /* if (arduboy.justPressed(A_BUTTON)) { // plays cry
        arduboy.waitForNextPlane();
        FX::disableOLED();
        ardvoice.playVoice(entry.cry, 0, arrayBuffer[entry.currententry], 0.55);
        FX::enableOLED();
        FX::display(CLEAR_BUFFER);
      }*/

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

      //handlecries();
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
