void balancingGameSetup();

const int TIME_DELAY_BALANCING_GAME = 10;

int ballPositionBalancingGame = int(strip1.endIndex / 2);
int ballVelocityBalancingGame = 2;
int tailLengthBalancingGame = 3;

int score = 0;
int scoreMiddleIndex = strip2.endIndex / 2;

#define TARGETS_COUNT  3
Target targets[TARGETS_COUNT];

int currentTime = 0;
int maxTime = 300;

void updateBallBalancingGame()
{
  for (int i = 0; i < tailLengthBalancingGame ; i++)
  {
    strip1.updateLedColor(ballPositionBalancingGame - i * ballVelocityBalancingGame, 0, 0, 0);
  }

  if (ballPositionBalancingGame + ballVelocityBalancingGame < strip1.startIndex) {
    Serial.print('h');
    ballVelocityBalancingGame *= -1;
  }

  if (ballPositionBalancingGame + ballVelocityBalancingGame > strip1.endIndex) {
    Serial.print('h');
    ballVelocityBalancingGame *= -1;
  }

  ballPositionBalancingGame += ballVelocityBalancingGame;

  strip1.updateLedColor(ballPositionBalancingGame, 255, 255, 255);

  for (int i = 1; i < tailLengthBalancingGame ; i++)
  {
    strip1.updateLedColor(ballPositionBalancingGame - i * ballVelocityBalancingGame, (int)(255 * (1.0 / (1 + (i * i)))), 0, 0);
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
      Serial.print("f");
      targets[i].kill();
      score--;
    }
  }
}

void resetBalancingGame() {
  strip1.clearLeds(strip1.startIndex,strip1.endIndex);
  strip2.clearLeds(strip2.startIndex,strip2.endIndex);

  ballPositionBalancingGame = int(strip1.endIndex / 2);
  ballVelocityBalancingGame = 2;
  tailLengthBalancingGame = 3;
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
      Serial.print("l");
      for(int i = 0; i < strip2.endIndex; i++){
        strip2.updateLedColor(i,195,0,0);
        delay(100);
        FastLED.show();
      }

    } else {
      Serial.print("w");
      for(int i = 0; i < strip2.endIndex; i++){
        strip2.updateLedColor(i,0,195,0);
        delay(100);
        FastLED.show();
      }

    }

    delay(7000); // wait for 7 seconds and reset
    balancingGameSetup();
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
  Serial.begin(115200);

  resetBalancingGame();
}


void balancingGameLoop()
{

  Usb.Task();
  drawTarget();

  updateBallBalancingGame();

  if(currentTime == maxTime)
  {
    currentTime = 0;
    addNewTarget();
  }
  else
    currentTime+=5;

  if (PS4.getButtonClick(CROSS)) {
    bool allMiss = true;

    for (int i = 0; i < TARGETS_COUNT; i ++){
      if(targets[i].alive() && targets[i].contains(ballPositionBalancingGame))
      {
        Serial.print("c");
        targets[i].kill();
        score++;
        allMiss = false;
      }
    }

    if(allMiss) {
      Serial.print("m");
    }

  }

  strip2.clearLeds(strip2.startIndex,strip2.endIndex);

  updateScoreDisplay();

  delay(TIME_DELAY_BALANCING_GAME);

}
