#pragma once
#include "Vector.h"
#define FRAME(x) x * 3 + arduboy.currentPlane()
#define MAX_FPS 45

struct Force {
  Vector gravity;
  Vector wind;
  Vector friction;
  Vector drag;
};

Force force = { (9.0, 0), (0.2, 0.5), (2, 2), (0,0) };
const uint8_t arraySize = 251;
uint16_t arrayBuffer[arraySize];  // Buffer to hold the data


uint8_t firstframe = 0;
int last_frame = -1;
uint8_t framewait = 2;
int prevTime=0;
int startcounter=0;
uint8_t gamestate =0;
struct Text {
  int x, y;
  int counter;
};
struct Camera {
  Vector position;
};
struct Sprite {
  uint8_t x, y;
  uint24_t sprite;
  uint8_t framecount;
  uint8_t currentframe;
  uint8_t framewait;
  int counter;
  bool inc;
};
struct Entry {
  uint8_t x, y;
  uint24_t namesprite;
  uint24_t textsprite;
  uint24_t cry;
  uint8_t currententry;
};
int scrollx =0;
int scrolly=0;
enum class Screen : uint8_t {
  Title,
  Game,
  Gallery,
  Gameover
};
uint8_t repeatDelay = 45;
uint8_t maxEntryIndex = 250;
uint8_t heldButton = 0;
uint8_t repeatDelayCount =0;
Camera camera = {0,-143};
Sprite sprite = {128-56,0,monsters,150, 0, 2, true};
Entry entry = {0, 8, namesgray, textentries, 0, 0};
Screen screen = {Screen::Title};
Text text = {0,0,0};

