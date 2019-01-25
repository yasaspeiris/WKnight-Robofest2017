
void colorsensorsetup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}
char checkcolor() {
  int rfreq, gfreq, bfreq = 0;
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25, 72, 255, 0);
  rfreq = frequency;
  // Printing the value on the serial monitor


  /*Serial.print("R= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");*/


  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 30, 90, 255, 0);
  gfreq = frequency;
  // Printing the value on the serial monitor


  /*Serial.print("G= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(100);*/

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25, 70, 255, 0);
  bfreq = frequency;
  // Printing the value on the serial monitor


  /*Serial.print("B= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.println("  ");
    delay(100);*/
  

  if (rfreq > bfreq && rfreq > gfreq) {
    return '#';
  }else if(bfreq > rfreq && bfreq > gfreq){
    return '&';
  }else if(gfreq > rfreq && gfreq > bfreq){
    return '$';
  }
}


