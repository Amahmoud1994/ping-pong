#include "FastLED.h"
#include "psUsb-read.h"
#include "Strip.h"
#include "Target.h"

#include "pong_game.h"
#include "balancing_game.h"


#define STRIP_1_PIN 3
#define STRIP_2_PIN 4


void setup()
{
  FastLED.addLeds<NEOPIXEL, STRIP_1_PIN>(strip1.leds, 270);
  FastLED.addLeds<NEOPIXEL, STRIP_2_PIN>(strip2.leds, 30);
  psSetup();
  balancingGameSetup();
}

void loop()
{

  balancingGameLoop();

  FastLED.show();
}
