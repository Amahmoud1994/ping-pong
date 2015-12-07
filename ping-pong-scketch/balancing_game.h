
int ballPosition = int(strip1.endIndex / 2);
int ballVelocity = 2;
int tailLength = 3;

int targetPosition = 0;
int targetRange = 10;
float targetIntensity = 200;
int targetHue = 127;

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
  targetPosition = targetRange + (int)(random(strip1.endIndex - 2*(targetRange)));
  targetRange = (int)(3+random(3));
  targetHue = random(255);
  targetIntensity = 200;
}
void drawTarget()
{
  for (int i = 0; i < targetRange ; i++)
  {
    strip1.updateLedHSV(targetPosition + i, targetHue, 255, targetIntensity);
    strip1.updateLedHSV(targetPosition - i, targetHue, 255, targetIntensity);

    targetIntensity -=.15;
    if(targetIntensity < 0)
    {
      addNewTarget();
      
    }
  }
}
void balancingGameSetup()
{

}



void balancingGameLoop()
{
  updateBall();

  Usb.Task();
  drawTarget();
  if (PS4.getButtonClick(DOWN) && abs(ballPosition- targetPosition) <targetRange) {
    addNewTarget();
  }
}
