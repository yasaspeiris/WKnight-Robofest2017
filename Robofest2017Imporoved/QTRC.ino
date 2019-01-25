void QTRCcallibrate() {
  digitalWrite(YELLOWLED, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode

  for (int i = 0; i < 100; i++)
  {
    qtrrc.calibrate();      // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  digitalWrite(YELLOWLED, LOW);
  delay(2000);
  digitalWrite(YELLOWLED, HIGH);

  for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();      // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  delay(300);
  digitalWrite(YELLOWLED, LOW);

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  delay(200);
}

void QTRCRead() {
  position = readLineo(sensorValues, QTR_EMITTERS_ON, 1); //0 for black 1 for white
  //Serial.println(position); // position falls between 0-5000 for 6 middle sensors.
  for (int x = 0; x < 10; x++) {
    sensorRead[x] = sensorValues[x];
    //Serial.print(sensorValues[x]);
    //Serial.print("    ");
  }

  for (int i = 0; i < 10; i++) {
    if (sensorRead[i] < 300) {
      sensorRead[i] = 1;

    } else {
      sensorRead[i] = 0;
    }
  }
  SensorPanelVal = (sensorRead[0] * 1) + (sensorRead[1] * 2) + (sensorRead[2] * 4) + (sensorRead[3] * 8) + (sensorRead[4] * 16) + (sensorRead[5] * 32) + (sensorRead[6] * 64) + (sensorRead[7] * 128) + (sensorRead[8] * 256) + (sensorRead[9] * 512);
  //Serial.println(SensorPanelVal);
}

int readLineo(unsigned int *sensor_values, unsigned char readMode, unsigned char white_line)
{
  unsigned char i, on_line = 0;
  unsigned long avg; // this is for the weighted total, which is long
  // before division
  unsigned int sum; // th

  qtrrc.readCalibrated(sensor_values, readMode);

  avg = 0;
  sum = 0;

  for (i = 0; i < 6; i++) {
    int value = sensor_values[i + 2];
    if (white_line)
      value = 1000 - value;

    // keep track of whether we see the line at all
    if (value > 200) {
      on_line = 1;
    }

    // only average in values that are above a noise threshold
    if (value > 50) {
      avg += (long)(value) * (i * 1000);
      sum += value;
    }
  }

  if (!on_line)
  {
    // If it last read to the left of center, return 0.
    if (_lastValue < (6 - 1) * 1000 / 2)
      return 0;

    // If it last read to the right of center, return the max.
    else
      return (6 - 1) * 1000;

  }

  _lastValue = avg / sum;

  return _lastValue;
}
