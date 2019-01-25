void nrfsetup() {
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}


void sendcolor(char message) {

  radio.stopListening();
  radio.write(&message, sizeof(message));
  Serial.println("SENT");
  delay(100);

}

void waitforack() {

  while (1) {
    radio.startListening();
    if (radio.available()) {
      char rmessage;
      radio.read(&rmessage, sizeof(rmessage));
      Serial.println(rmessage);
     break;
    }

  }
}

