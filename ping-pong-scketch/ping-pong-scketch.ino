#include "FastLED.h"
#include "ps3usb-read.h"

// How many leds in your strip?
#define NUM_LEDS 270
#define START_INDEX 0
#define END_INDEX NUM_LEDS
#define DATA_PIN 3
#define TIME_DELAY 10


int ballPosition = int(NUM_LEDS / 2);
int ballVelocity = 2;
int tailLength = 9;

int player1Bat = 0;
int player1BatVelocity = 0;
int player1Score = 0;

int player2Bat = 0;
int player2BatVelocity = 0;
int player2Score = 0;

int batMaxLength = 10;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  ps3Setup();
}

void updateBats() {

    if (player1Bat + player1BatVelocity > batMaxLength){
      player1BatVelocity *= -1;
    } else if (player1Bat + player1BatVelocity < 0){
      player1BatVelocity = 0;
    }

    player1Bat += player1BatVelocity;

    if (player2Bat + player2BatVelocity > batMaxLength) {
      player2BatVelocity = -1;
    } else if (player2Bat + player2BatVelocity < 0) {
      player2BatVelocity = 0;
    }

    player2Bat += player2BatVelocity;

}

void drawBats(int r, int g , int b) {

  for (int i = START_INDEX; i < player1Bat; i++)
  {
    updateLedColor(i, 0 * r, 127 * g, 0 * b);
  }

  for (int i = END_INDEX; i > END_INDEX - player2Bat; i--)
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
  for (int i = 0; i < tailLength ; i++)
  {
    updateLedColor(ballPosition - i * ballVelocity, 0, 0, 0);
  }
  if((player1Bat != 0 && ballPosition + ballVelocity < START_INDEX + player1Bat) || 
      (player2Bat != 0 && ballPosition + ballVelocity > END_INDEX - player2Bat)) {
    ballVelocity *= -1;
  }   
  else if (ballPosition + ballVelocity < START_INDEX){
    player2Score ++;
    resetBallPosition();
  }
  else if (ballPosition + ballVelocity > END_INDEX){
    player1Score ++;
    resetBallPosition();
  }


  ballPosition += ballVelocity;

  for (int i = 0; i < tailLength ; i++)
  {
    updateLedColor(ballPosition - i * ballVelocity, (int)(255 * (1.0 / (1 + (i * i)))), 0, 0);
  }
  FastLED.show();
  delay(TIME_DELAY);
}

void resetBallPosition()
{
  delay(1000);
  Serial.print("\n player 1 score : ");
  Serial.print(player1Score);
  Serial.print("\n player 2 score : ");
  Serial.print(player2Score);
  ballPosition = int(NUM_LEDS / 2);
  ballVelocity = 2;
}

void loop()
{
  updateBall();
  drawBats(0, 0, 0);

  Usb.Task();

  if (PS3.getButtonClick(LEFT) && player1BatVelocity == 0 ) {
      player1BatVelocity = 1;
  }

  if (PS3.getButtonClick(RIGHT) && player2BatVelocity == 0) {
      player2BatVelocity = 1;
  }

  updateBats();

  drawBats(1, 1, 1);
}

bool inBounds(int position) {
  return position >= START_INDEX && position < END_INDEX;
}
