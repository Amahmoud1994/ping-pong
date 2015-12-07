
int ballPosition = int(strip1.endIndex / 2);
int ballVelocity = 2;
int tailLength = 3;

Target target1;

void updateBall()
{
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
void addNewTarget()
{
  strip1.clearLeds(strip1.startIndex, strip1.endIndex);
  target1.spawn();
}
void drawTarget()
{
  target1.draw();
}
void balancingGameSetup()
{

}



void balancingGameLoop()
{
  updateBall();

  Usb.Task();
  drawTarget();
  if (PS4.getButtonClick(DOWN) && target1.contains(ballPosition)) {
    target1.kill();
  }
}
