#include "Arduino.h"
int player1_button = 4;
int player2_button = 5;
int lastButtonState1 = 1;
int lastButtonState2 = 1;
int buttonState;

void setupReading() {
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(player1_button, INPUT);
  digitalWrite(player1_button, HIGH);
  pinMode(player2_button, INPUT);
  digitalWrite(player2_button, HIGH);
}
// the loop routine runs over and over again forever:
bool checkBtn1() {
  bool res = false;
  int buttonState = digitalRead(player1_button);
  if(buttonState != lastButtonState1 && buttonState == 0)
  {
    res = true;
    Serial.println("p1");
  }  
  lastButtonState1 = buttonState;
  return res;
}
bool checkBtn2() {
  bool res = false;
  int buttonState = digitalRead(player2_button);
  if(buttonState != lastButtonState2 && buttonState == 0)
  {
    res = true;
    Serial.println("p2");
  }  
  lastButtonState2 = buttonState;
  return res;
}
