int player1_button = 2;
int player2_button = 3;
int lastButtonState1 = 1;
int lastButtonState2 = 1;
int buttonState;

void setup() {
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(player1_button, INPUT);
  digitalWrite(player1_button, HIGH);
  pinMode(player2_button, INPUT);
  digitalWrite(player2_button, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:

  buttonState = digitalRead(player1_button);
  if(buttonState != lastButtonState1 && buttonState == 0)
    Serial.println("p1");
  lastButtonState1 = buttonState;
  
  buttonState = digitalRead(player2_button);
  if(buttonState != lastButtonState2 && buttonState == 0)
    Serial.println("p2");
  lastButtonState2 = buttonState;
  
  delay(1);        // delay in between reads for stability
}
