void setup() {
  Serial.begin(115200);
  motorsetup();
  servosetup();
  lightsandswsetup();
  colorsensorsetup();
  nrfsetup();
  //vlxsetup();
}

void loop() {
  int val1 = digitalRead(STARTSWITCH);
  int val2 = digitalRead(MODESW);
  int val3 = digitalRead(CALSW);


  if ( val1 == 0) {

    digitalWrite(BLUELED, HIGH);
    delay(1000);
    maze_solve();
    gotostart();
    while (1) {
      int val1 = digitalRead(STARTSWITCH);
      if ( val1 == 0) {
        travelmappedmaze();
      }
    }
  }

  if (val3 == 0) {
    digitalWrite(YELLOWLED, HIGH);
    QTRCcallibrate();
    digitalWrite(YELLOWLED, LOW);
  }
  if (val2 == 0) {
    linedegreetravel('L', TURNSPEED);
  }

}
