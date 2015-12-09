#include "FastLED.h"
#include "psUsb-read.h"
#include "Strip.h"
#include "Target.h"

#include "pong_game.h"
#include "balancing_game.h"

const int PING_PONG = 0;
const int BALANCING_GAME = 1;

int mode = PING_PONG;

#define STRIP_1_PIN 3
#define STRIP_2_PIN 4


void setup()
{
  FastLED.addLeds<NEOPIXEL, STRIP_1_PIN>(strip1.leds, strip1.endIndex);
  FastLED.addLeds<NEOPIXEL, STRIP_2_PIN>(strip2.leds, strip2.endIndex);
  psSetup();

  pongGameSetup();
}

void loop()
{

  if (PS4.getButtonClick(R1)) {
    if(mode == PING_PONG) {
      balancingGameSetup();
      mode = BALANCING_GAME;
    }
    else {
      pongGameSetup();
      mode = PING_PONG;
    }
  }

  if(mode == PING_PONG){
    pongGameLoop();
  } else {
    balancingGameLoop();
  }

  FastLED.show();
}
