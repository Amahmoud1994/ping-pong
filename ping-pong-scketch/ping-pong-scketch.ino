#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 29
#define start_index 0
#define end_index NUM_LEDS
#define DATA_PIN 3
#define CLOCK_PIN 13
#define time_delay 30
int ball_pos = int(NUM_LEDS / 2);
int ball_dir = 2;
int player1_bat = start_index;
int player1_bat_dir = 1;
int player2_bat = end_index;
int player2_bat_dir = -1;
int bat_max = 5;

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
  if(player == 1)
  {
    //will check for which player later
    if(player1_bat + player1_bat_dir > bat_max || player1_bat + player1_bat_dir < 0)
     player1_bat_dir *= -1;
    player1_bat += player1_bat_dir;   
  }
  else
  {
    //will check for which player later
    if(player2_bat + player2_bat_dir > bat_max || player2_bat + player2_bat_dir < 0)
     player2_bat_dir *= -1;
    player2_bat += player2_bat_dir;
  }
}
void drawBat(int r,int g ,int b,int startIndex,int bat_length, int dir) {
  for (int i = startIndex; (startIndex+(dir*bat_length))-i < 1; i += dir)
  {
    updateLedColor(i, r, g, b);
  }
}
void updateLedColor(int pos, int r, int g, int b) {
  if (inBounds(pos)) {
    leds[pos].r = r;
    leds[pos].g = g;
    leds[pos].b = b;
  }
}
void loop()
{
  drawBat(0,0,0,start_index,player1_bat,1);
  drawBat(0,0,0,end_index-1,player2_bat,-1);
  updateBat(1);
  updateBat(2);
  drawBat(0,0,127,start_index,player1_bat,1);
  drawBat(0,127,0,end_index-1,player2_bat,-1);
  
  for (int i = 0; i < 5 ; i++)
  {
    updateLedColor(ball_pos - i * ball_dir, 0, 0, 0);
  }
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
