void resetPongGame();
void pongGameSetup();

const int TIME_DELAY = 1;

int ballPosition = int(strip1.endIndex / 2);
int ballVelocity = 2;
int tailLength = 9;

int player1Bat = 0;
int player1BatVelocity = 0;
int player1Score = 0;

int player2Bat = 0;
int player2BatVelocity = 0;
int player2Score = 0;

int batMaxLength = 6;
int gameRound = 0;

void updateBats() {

    int coolDown = -30;
    if (player1Bat + player1BatVelocity > batMaxLength){
      player1BatVelocity *= -1;
    } else if (player1Bat + player1BatVelocity < coolDown){
      player1BatVelocity = 0;
      player1Bat = 0;
    }

    player1Bat += player1BatVelocity;

    if (player2Bat + player2BatVelocity > batMaxLength) {
      player2BatVelocity = -1;
    } else if (player2Bat + player2BatVelocity < coolDown) {
      player2BatVelocity = 0;
      player2Bat = 0;

    }

    player2Bat += player2BatVelocity;

}

void drawBats(int r, int g , int b) {

  for (int i = strip1.startIndex; i < player1Bat; i++)
  {
    strip1.updateLedColor(i, 0 * r, 127 * g, 0 * b);
  }

  for (int i = strip1.endIndex; i > strip1.endIndex - player2Bat; i--)
  {
    strip1.updateLedColor(i, 0 * r, 0 * g, 127 * b);
  }

}

void resetBallPosition()
{
  ballPosition = int(strip1.endIndex / 2);
  ballVelocity = 2;
  ballVelocity *= (random(2) == 1 ? -1:1);

  player1Bat = 0;
  player1BatVelocity = 0;

  player2Bat = 0;
  player2BatVelocity = 0;

  strip1.clearLeds(strip1.startIndex,strip1.endIndex);

  FastLED.show();
  delay(1000);
  Serial.print("s");
}

void updateBall()
{

  // turn off the ball & the trail
  for (int i = 0; i < tailLength ; i++)
  {
    strip1.updateLedColor(ballPosition - i * ballVelocity, 0, 0, 0);
  }
  if((player1Bat != 0 && ballPosition + ballVelocity < strip1.startIndex + player1Bat)) {
    Serial.print("h");
    strip1.clearLeds(strip1.startIndex,player1Bat);
    ballVelocity *= -1;
  }else if(player2Bat != 0 && ballPosition + ballVelocity > strip1.endIndex - player2Bat){
    Serial.print("h");
    strip1.clearLeds(player2Bat,strip1.endIndex);
    ballVelocity *= -1;
  }
  else if (ballPosition + ballVelocity < strip1.startIndex){
    Serial.print("g");
    player2Score ++;
    strip2.updateLedColor(gameRound,0,0,255);
    gameRound++;
    resetBallPosition();
  }
  else if (ballPosition + ballVelocity > strip1.endIndex){
    Serial.print("g");
    player1Score ++;
    strip2.updateLedColor(gameRound,0,255,0);
    gameRound++;
    resetBallPosition();
  }

  ballPosition += ballVelocity;

  strip1.updateLedColor(ballPosition,255,255,255);

  for (int i = 1; i < tailLength ; i++)
  {
    strip1.updateLedColor(ballPosition - i * ballVelocity, (int)(255 * (1.0 / (1 + (i * i)))), 0, 0);
  }

}

void resetPongGame() {
  strip1.clearLeds(strip1.startIndex,strip1.endIndex);
  strip2.clearLeds(strip2.startIndex,strip2.endIndex);

  ballPosition = int(strip1.endIndex / 2);
  ballVelocity = 2;
  tailLength = 9;
  player1Bat = 0;
  player1BatVelocity = 0;
  player1Score = 0;
  player2Bat = 0;
  player2BatVelocity = 0;
  player2Score = 0;
  batMaxLength = 10;
  gameRound = 0;
}

void updateRoundStatus(){
  if(gameRound == 29) {
    strip2.clearLeds(strip2.startIndex,strip2.endIndex);

    if(player1Score > player2Score) {
      for(int i = 0; i < strip2.endIndex; i++){
        strip2.updateLedColor(i,0,255,0);
        delay(100);
        FastLED.show();
      }
    }
    else {
      for(int i = 0; i < strip2.endIndex; i++){
        strip2.updateLedColor(i,0,0,255);
        delay(100);
        FastLED.show();
      }
    }

    delay(5000); // wait for 5 seconds and reset
    pongGameSetup();
  }
}

void pongGameSetup()
{
  Serial.begin(115200);
  resetPongGame();
}

void pongGameLoop()
{

  updateRoundStatus();

  updateBall();
  drawBats(0, 0, 0);

  Usb.Task();

  if (PS4.getButtonClick(LEFT) && player1BatVelocity == 0 ) {
      Serial.print("b");
      player1BatVelocity = 1;
  }

  if (PS4.getButtonClick(CIRCLE) && player2BatVelocity == 0) {
      Serial.print("b");
      player2BatVelocity = 1;
  }

  updateBats();

  drawBats(1, 1, 1);

  delay(TIME_DELAY);

}
