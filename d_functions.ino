void getTemperatureAndHumidity() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Nie udało się odczytać danych z czujnika DHT!"));
  }
  else {
    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print(F(" Wilgotność: "));
    Serial.print(h);
    Serial.print(F("%  Temperatura: "));
    Serial.print(t);
    Serial.print(F("C "));
    Serial.print(f);
    Serial.print(F("F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("C "));
    Serial.print(hif);
    Serial.println(F("F"));
  }

  lastMeasurement = millis();
  change = true;
}

void updateLED() {
  if (turnLightOn == true) {
    if (t >= 17.5 && t < 25) { // good temperature
      setLEDColor(GREEN);
    }
    else if ((t >= 25 && t < 30) || (t >= 15 && t < 17.5)) { // medium temperature
      setLEDColor(ORANGE);
    }
    else if ((t >= 30) || (t < 15)) { // bad temperature
      setLEDColor(RED);
    }
  }
  else {
    setLEDColor(BLACK);
  }
}

void setLEDColor(long color) {
  int b = color % 0x100;
  int g = (color - b) / 0x100 % 0x100;
  int r = (color - g) / 0x10000;
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void checkForButtonPress() {
  buttonReading = readAnalogToDigital(buttonPin);

  if (buttonReading == true && previousButtonReading == false) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      view = !view;
      change = true;
      lastDebounceTime = millis();
    }
  }
  previousButtonReading = buttonReading;
}

void getPositionsFromPotentiometer() {
  potentiometer = analogRead(potentiometerPin);
  if (view == false) {
    temporary = potentiometer / (POTENTIOMETER_RANGE / TEMP_POSSIBILITIES);
    tempPosition = temporary;
    if (previousTempPosition = !tempPosition) {
      change = true;
      previousTempPosition = tempPosition;
    }
  } else {
    temporary = potentiometer / (POTENTIOMETER_RANGE / HUMI_POSSIBILITIES);
    humiPosition = temporary;
    if (previousHumiPosition = !humiPosition) {
      change = true;
      previousHumiPosition = humiPosition;
    }
  }
}

void checkForSound() {
  sound = analogRead(soundPin);

  if (sound > previousSound + soundDifference) {
    soundOn = true;
  }
  else {
    soundOn = false;
  }
  soundChanged = false;
  if (soundOn == true && previousSoundOn == false) {
    if ((millis() - lastSoundChange) > soundDelay) {
      lastSoundChange = millis();
      turnLightOn = !turnLightOn;
      soundChanged = true;
    }
  }
  previousSoundOn = soundOn;
  previousSound = sound;
}

void getInfraredReading() {
  if (IrReceiver.decode()) {
    int command = IrReceiver.decodedIRData.command;
    int address = IrReceiver.decodedIRData.address;
    int rawData = IrReceiver.decodedIRData.decodedRawData;
    Serial.print(command);

    IrReceiver.resume();
  }
}

void updateDisplay() {
  if (view == false) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Temperatura");
    lcd.setCursor(tempPosition, 1);
    lcd.print(t);
    lcd.setCursor(tempPosition + 6, 1);
    lcd.write(2);
    lcd.print("C");
  } else {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Wilgotno");
    lcd.write(0);
    lcd.write(1);
    lcd.setCursor(humiPosition, 1);
    lcd.print(h);
    lcd.setCursor(humiPosition + 5, 1);
    lcd.print("%");
  }
  change = false;
}

void writeTimer() {
  timer = 1 + (measureBreak - (millis() - lastMeasurement)) / 1000;
  writeNumberFour(timer, -1);
}

void writeNumberFour(int number, int point) {
  int numbers[4];
  numbers[0] = number % 10;
  numbers[1] = ((number % 100) - (number % 10)) / 10;
  numbers[2] = ((number % 1000) - (number % 100)) / 100;
  numbers[3] = ((number % 10000) - (number % 1000)) / 1000;

  if (point >= 0 && point < 4) numbers[point] += 16;

  bool displayZeros = false;
  for (int i = 3; i >= 0; i--) {
    if (numbers[i] != 0 || displayZeros) {
      writeNumberSingle(numbers[i]);
      digitalWrite(digits[i], 0);
      delay(5);
      digitalWrite(digits[i], 1);
      displayZeros = true;
    }
  }
}

void writeNumberSingle(int number) { // 1 digit display
  bool point = false;
  if (number >= 16) point = true;
  switch (number) {
    case 31:
    case 15: writeShiftRegister(F, point);
      break;
    case 30:
    case 14: writeShiftRegister(E, point);
      break;
    case 29:
    case 13:  writeShiftRegister(D, point);
      break;
    case 28:
    case 12:  writeShiftRegister(C, point);
      break;
    case 27:
    case 11:  writeShiftRegister(B, point);
      break;
    case 26:
    case 10: writeShiftRegister(A, point);
      break;
    case 25:
    case 9: writeShiftRegister(NINE, point);
      break;
    case 24:
    case 8: writeShiftRegister(EIGHT, point);
      break;
    case 23:
    case 7: writeShiftRegister(SEVEN, point);
      break;
    case 22:
    case 6: writeShiftRegister(SIX, point);
      break;
    case 21:
    case 5: writeShiftRegister(FIVE, point);
      break;
    case 20:
    case 4: writeShiftRegister(FOUR, point);
      break;
    case 19:
    case 3: writeShiftRegister(THREE, point);
      break;
    case 18:
    case 2: writeShiftRegister(TWO, point);
      break;
    case 17:
    case 1: writeShiftRegister(ONE, point);
      break;
    case 16:
    case 0: writeShiftRegister(ZERO, point);
      break;
    default: writeShiftRegister(dash, true);
  }
}

void writeShiftRegister(const byte shiftRegister[], bool dot) {
  digitalWrite(showDisplayPin, LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(clockDisplayPin, LOW);
    digitalWrite(dataDisplayPin, shiftRegister[i]);
    digitalWrite(clockDisplayPin, HIGH);
  }
  digitalWrite(clockDisplayPin, LOW);
  digitalWrite(dataDisplayPin, dot);
  digitalWrite(clockDisplayPin, HIGH);

  digitalWrite(showDisplayPin, HIGH);
}

int readAnalogToDigital(int pin) {
  int pinRead = analogRead(pin);
  if (pinRead > POTENTIOMETER_RANGE / 2) return true;
  else return false;
}
