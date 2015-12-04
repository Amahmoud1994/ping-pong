#define TIME_DELAY 10

int ballPosition = int(strip1.endIndex / 2);
int ballVelocity = 2;
int tailLength = 9;

void updateBall()
{
  // turn off the ball & the trail
  for (int i = 0; i < tailLength ; i++)
  {
    strip1.updateLedColor(ballPosition - i * ballVelocity, 0, 0, 0);
  }
  if (ballPosition + ballVelocity < strip1.startIndex) {
    ballVelocity *= -1;
  }
  if (ballPosition + ballVelocity > strip1.endIndex) {
   ballVelocity *= -1;
  }
  ballPosition += ballVelocity;

  strip1.updateLedColor(ballPosition, 255, 255, 255);

  for (int i = 1; i < tailLength ; i++)
  {
    strip1.updateLedColor(ballPosition - i * ballVelocity, (int)(255 * (1.0 / (1 + (i * i)))), 0, 0);
  }
}
void balancingGameSetup()
{

}

void balancingGameLoop()
{
  updateBall();

  Usb.Task();

  if (PS3.getButtonClick(DOWN)) {
    //player2BatVelocity = 1;
  }
}
