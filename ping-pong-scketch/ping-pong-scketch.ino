#include "FastLED.h"
#include "ps3usb-read.h"
#include "Strip.h"
#include "pong_game.h"

#define STRIP_1_PIN 3
#define STRIP_2_PIN 4
#define TIME_DELAY 10

void setup()
{
  FastLED.addLeds<NEOPIXEL, STRIP_1_PIN>(strip1.leds, 270);
  FastLED.addLeds<NEOPIXEL, STRIP_2_PIN>(strip2.leds, 30);
  ps3Setup();
}

void loop()
{
  pongGameLoop();

  delay(TIME_DELAY);
  FastLED.show();
}
