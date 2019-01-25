void getdistance() {
  int distance1,distance2,distance3,distance4,distance5;
  delay(50);
  distance1 = sonar1.ping_median() / 57;

  delay(50);
  distance2 = sonar2.ping_median() / 57;

  delay(50);
  distance3 = sonar3.ping_median() / 57;

  delay(50);
  distance4 = sonar4.ping_median() / 57;

  delay(50);
  distance5 = sonar5.ping_median() / 57;



  Serial.print("Sonar 1 : ");
  Serial.println(distance1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("Sonar 2 : ");
  Serial.println(distance2);
  Serial.print("Sonar 3 : ");
  Serial.println(distance3); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("Sonar 4 : ");
  Serial.println(distance4);
  Serial.print("Sonar 5 : ");
  Serial.println(distance5);
}

void pingfront() {
  front = (sonar3.ping()/58); 
  
  delay(10);
}

void pingright(){
  right = (sonar4.ping()/58);
  Serial.println(right);
  delay(10);
}

void pingleft(){
  left = (sonar5.ping()/58);
  delay(10);
}

void pingslantleft(){
  slantleft = (sonar1.ping()/58);
  delay(10);
}

void pingslantright(){
  slantright = (sonar2.ping()/58);
  delay(10);
}

