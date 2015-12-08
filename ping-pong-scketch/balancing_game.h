const int TIME_DELAY = 10;

int ballPosition = int(strip1.endIndex / 2);
int ballVelocity = 2;
int tailLength = 3;

int score = 0;
int scoreMiddleIndex = strip2.endIndex / 2;

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
  for (int i = 0; i < TARGETS_COUNT; i ++){
    targets[i].draw();

    if(targets[i].intensity < 0 && targets[i].alive())
    {
      targets[i].kill();
      score--;
    }
  }
}

void resetBalancingGame() {
  strip1.clearLeds(strip1.startIndex,strip1.endIndex);
  strip2.clearLeds(strip2.startIndex,strip2.endIndex);

  ballPosition = int(strip1.endIndex / 2);
  ballVelocity = 2;
  tailLength = 3;
  score = 0;
  scoreMiddleIndex = strip2.endIndex / 2;
  currentTime = 0;
  maxTime = 300;

  for (int i = 0; i < TARGETS_COUNT; i++){
    targets[i].kill();
  }
}


void updateScoreDisplay(){

  if(abs(score) >= scoreMiddleIndex) { // game over :(

    strip2.clearLeds(strip2.startIndex,strip2.endIndex);

    if(score < 0) { // game lost
      for(int i = 0; i < strip2.endIndex; i++){
        strip2.updateLedColor(i,195,0,0);
        delay(100);
        FastLED.show();
      }

    } else {

      for(int i = 0; i < strip2.endIndex; i++){
        strip2.updateLedColor(i,0,195,0);
        delay(100);
        FastLED.show();
      }

    }

    delay(5000); // wait for 5 seconds and reset
    resetBalancingGame();
    return;
  }

  for (int i = 0; i < abs(score); i++) {
    if(score > 0) {
      strip2.updateLedColor(scoreMiddleIndex+i,0,195,0);
    }else{
      strip2.updateLedColor(scoreMiddleIndex-i,195,0,0);
    }
  }

}

void balancingGameSetup()
{
  for (int i = 0; i < TARGETS_COUNT; i ++)
    targets[i].kill();
}


void balancingGameLoop()
{

  Usb.Task();
  drawTarget();

  updateBall();

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
          targets[i].kill();
          score++;
        }
  }

  strip2.clearLeds(strip2.startIndex,strip2.endIndex);

  updateScoreDisplay();

  Serial.println(score);

  delay(TIME_DELAY);

}
