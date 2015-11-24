#include "FastLED.h"

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
void drawBat(int r,int g ,int b) {
  for (int i = start_index; i < player1_bat; i ++)
  {
    updateLedColor(i, 0*r, 127*g, 0*b);
  }
  for (int i = end_index; i > end_index-player2_bat; i--)
  {
    updateLedColor(i, 0*r, 0*g, 127*b);
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
  /*drawBat(0,0,0);
  updateBat(1);
  updateBat(2);
  drawBat(1,1,1);
  */
}
void SFXattacking(){
    int freq = map(sin(millis()/2.0)*1000.0, -1000, 1000, 500, 600);
    if(random8(5)== 0){
      freq *= 3;
    }
    toneAC(freq, MAX_VOLUME);
}
void SFXdead(){
    int freq = max(1000 - (millis()-killTime), 10);
    freq += random8(200);
    int vol = max(10 - (millis()-killTime)/200, 0);
    toneAC(freq, MAX_VOLUME);
}
void SFXkill(){
    toneAC(2000, MAX_VOLUME, 1000, true);
}
void SFXwin(){
    int freq = (millis()-stageStartTime)/3.0;
    freq += map(sin(millis()/20.0)*1000.0, -1000, 1000, 0, 20);
    int vol = 10;//max(10 - (millis()-stageStartTime)/200, 0);
    toneAC(freq, MAX_VOLUME);
}

void SFXcomplete(){
    noToneAC();
}
