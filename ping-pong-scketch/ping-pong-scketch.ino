#include "FastLED.h"
#include "Particle.h"

// How many leds in your strip?
#define NUM_LEDS 29
#define start_index 0
#define end_index NUM_LEDS
#define DATA_PIN 3
#define CLOCK_PIN 13
#define time_delay 30
int ball_pos = int(NUM_LEDS / 2);
int ball_dir = 1;
int player1_bat = 0;
int player1_bat_dir = 1;
int player2_bat = 0;
int player2_bat_dir = 1;
int bat_max = 5;

int const particleCount = 40;
Particle particlePool[40] = {
  Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle(), Particle()
};
// Define the array of leds
CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}
bool inBounds(int x) {
  return x >= start_index && x < end_index;
}
void updateBat(int player) {
  if (player == 1)
  {
    //will check for which player later
    if (player1_bat + player1_bat_dir > bat_max)
      player1_bat_dir = -1;
    else if (player1_bat + player1_bat_dir < 0)
      player1_bat_dir *= 0;
    player1_bat += player1_bat_dir;
  }
  else
  {
    //will check for which player later
    if (player2_bat + player2_bat_dir > bat_max)
      player2_bat_dir = -1;
    else if (player2_bat + player2_bat_dir < 0)
      player2_bat_dir = 0;
    player2_bat += player2_bat_dir;
  }
}
void drawBat(int r, int g , int b) {
  for (int i = start_index; i < player1_bat; i ++)
  {
    updateLedColor(i, 0 * r, 127 * g, 0 * b);
  }
  for (int i = end_index; i > end_index - player2_bat; i--)
  {
    updateLedColor(i, 0 * r, 0 * g, 127 * b);
  }
}
void updateLedColor(int pos, int r, int g, int b) {
  if (inBounds(pos)) {
    leds[pos].r = r;
    leds[pos].g = g;
    leds[pos].b = b;
  }
}
void updateBall()
{
  // turn off the ball & the trail
  for (int i = 0; i < 5 ; i++)
  {
    updateLedColor(ball_pos - i * ball_dir, 0, 0, 0);
  }
  FastLED.show();
  delay(time_delay);
  if (!inBounds(ball_pos + ball_dir))
    ball_dir *= -1;
  ball_pos += ball_dir;
  for (int i = 0; i < 5 ; i++)
  {
    updateLedColor(ball_pos - i * ball_dir, (int)(127 * (1.0 / (1 + (i * i)))), 0, 0);
  }
  FastLED.show();
  delay(time_delay);
}
void loop()
{
  updateBall();
  drawBat(0, 0, 0);
  updateBat(1);
  updateBat(2);
  drawBat(1, 1, 1);
}
int getLED(int pos) {
  // The world is 1000 pixels wide, this converts world units into an LED number
  return constrain((int)map(pos, 0, 1000, 0, NUM_LEDS - 1), 0, NUM_LEDS - 1);
}

bool tickParticles() {
  bool stillActive = false;
  for (int p = 0; p < particleCount; p++) {
    if (particlePool[p].Alive()) {
      particlePool[p].Tick(0);
      leds[getLED(particlePool[p]._pos)] += CRGB(particlePool[p]._power, 0, 0);
      stillActive = true;
    }
  }
  return stillActive;
}

