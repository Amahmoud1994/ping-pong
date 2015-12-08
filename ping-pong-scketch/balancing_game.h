const int TIME_DELAY = 25;

int ballPosition = int(strip1.endIndex / 2);
int ballVelocity = 2;
int tailLength = 3;


#define TARGETS_COUNT  3
Target targets[TARGETS_COUNT];

int currentTime = 0;
int maxTime = 300;

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

int getFirstDead()
{
  for (int i = 0; i < TARGETS_COUNT; i ++)
    if(!targets[i].alive())
      return i;
  return -1;
}

void addNewTarget()
{

  int index = getFirstDead();
  if(index != -1)
  {
    targets[index].spawn();
  }

}

void drawTarget()
{
  for (int i = 0; i < TARGETS_COUNT; i ++)
    targets[i].draw();
}

void balancingGameSetup()
{
  for (int i = 0; i < TARGETS_COUNT; i ++)
    targets[i].kill();
}

void balancingGameLoop()
{
  updateBall();

  Usb.Task();
  drawTarget();

  if(currentTime == maxTime)
  {
    currentTime = 0;
    addNewTarget();
  }
  else
    currentTime+=5;

  if (PS4.getButtonClick(CROSS)) {
    for (int i = 0; i < TARGETS_COUNT; i ++)
      if(targets[i].alive() && targets[i].contains(ballPosition))
        {
          Serial.print(i);
          targets[i].kill();
        }
  }


  delay(TIME_DELAY);

}
