void wallfollow(int power) {
  MasterENC.write(0) ; SlaveENC.write(0); totalTicks = 0; error = 0; lasterror = 0;
  MaxPower = power;
  MasterPower = power; SlavePower = power;
  while (1) {
    SetMasterPower(MasterPower); SetSlavePower(SlavePower);
    pingright(); pingright(); pingslantleft(); pingslantright();
    if (right > 0 && right < 14) {
      error =  right - 10;
    } else if (slantright > 0 && slantright < 30) {
      error =  slantright - 18;
    } else if (right == 0 && slantright == 0) {
      error = 3;
    }
    if (left > 0 ) {
      break;
    }
    //Serial.println(error);
    int delta = error - lasterror;
    int change = (error * 9) + (delta * 60 ); //+ (sumerr * 0.0028); // (error * 1/7) + (delta * 4)
    lasterror = error;
    sumerr += error;

    MasterPower = MaxPower + change;
    MasterPower = constrain(MasterPower, 20, 100);
    SlavePower  = MaxPower - change;
    SlavePower = constrain(SlavePower, 20, 100);

    //Serial.print("Slave = "); Serial.println(SlavePower); Serial.print("Master = "); Serial.println(MasterPower);
    totalTicks += MasterENC.read(); MasterENC.write(0); SlaveENC.write(0);
  } while (1) {
    if (left > 0) {
      error =  left - 10;
    } else if ( left == 0 && slantleft > 0) {
      error =  slantleft - 10;
    } else if (left == 0 && slantleft == 0) {
      error = 10;
    }
    //Serial.println(error);
    int delta = error - lasterror;
    int change = (error * 9) + (delta * 60 ); //+ (sumerr * 0.0028); // (error * 1/7) + (delta * 4)
    lasterror = error;
    sumerr += error;

    MasterPower = MaxPower - change;
    MasterPower = constrain(MasterPower, 0, 170);
    SlavePower  = MaxPower + change;
    SlavePower = constrain(SlavePower, 0, 170);

    //Serial.print("Slave = "); Serial.println(SlavePower); Serial.print("Master = "); Serial.println(MasterPower);
    totalTicks += MasterENC.read(); MasterENC.write(0); SlaveENC.write(0);
    QTRCRead();
    if (SensorPanelVal = 1023) {
      break;
    }
  }

  setBrakes(250, 250);
  analogWrite(11, 120);
  delay(20);
  analogWrite(11, 0);
  MaxPower = 0;

}



void lastpart() {
  inchtravel(8, 120);
  char b = nodetravel(120);
  delay(200);
  b = nodetravel(120);
  delay(200);
  b = nodetravel(120);
}

