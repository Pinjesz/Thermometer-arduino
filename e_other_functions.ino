void getTemperatureAndHumidity() {
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Nie udało się odczytać danych z czujnika DHT!"));
  }
  else {
    Serial.print(F("Temperatura: "));
    Serial.print(t);
    Serial.print(F("℃"));
    Serial.print(F(" Wilgotność: "));
    Serial.print(h);
    Serial.println(F("%"));
  }

  updateDisplayLCD = true;
  updateColorLED = true;
  lastMeasurement = millis();
  timer = measureBreak;
  timerChanger = 0;

  Serial.println(analogRead(lightPin));
  previousSound = MAX_ANALOG_READ;
}


void setRGB(long color) {
  int b = color % 0x100;
  int g = (color - b) / 0x100 % 0x100;
  int r = (color - g) / 0x10000;
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}


void writeFourDigits(int number, int point) {
  writePrepare(number, point);
  for (int i = 3; i >= 0; i--) {
    place = i;
    writeSingleNumber();
  }
}

void writeDigitsOneByOne(int number, int point) {
  switch (place) {
    case 3:
      writePrepare(number, point);
    case 2:
    case 1:
    case 0:
      writeSingleNumber();
      break;
  }
}

void writePrepare(int number, int point) {
  numbers[0] = number % 10;
  numbers[1] = ((number % 100) - (number % 10)) / 10;
  numbers[2] = ((number % 1000) - (number % 100)) / 100;
  numbers[3] = ((number % 10000) - (number % 1000)) / 1000;

  if (point >= 0 && point < 4) numbers[point] += 16;

  displayZeros = false;
}

void writeSingleNumber() {
  if (numbers[place] != 0 || displayZeros) {
    displayNumberSingle(numbers[place]);
    digitalWrite(digits[place], 0);
    delayMicroseconds(displayDelay);
    digitalWrite(digits[place], 1);
    displayZeros = true;
  }
}

void updatePlace() {
  --place;
  if (place == -1) place = 3;
}

void executeCommand() {
  switch (command) {
    case BUTTON_PLAY:
      turnLightOn = !turnLightOn;
      updateColorLED = true;
      break;
    case BUTTON_PREV:
    case BUTTON_NEXT:
      view = !view;
      updateDisplayLCD = true;
      break;
    case BUTTON_VOLplus:
      timerChanger += 5;
      break;
    case BUTTON_VOLminus:
      timerChanger -= 5;
      break;
    case BUTTON_0:
      timerChanger = - (int)measureBreak;
      break;
    case BUTTON_100:
      timerChanger += 100;
      break;
    case BUTTON_200:
      timerChanger += 200;
      break;
    case BUTTON_CHminus:
    case BUTTON_CH:
    case BUTTON_CHplus:
      displayMode = !displayMode;
      displayDelay = 40 - displayDelay;
      break;
    default:
      break;
  }
}


void displayNumberSingle(int number) { // 1 digit display
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
  if (pinRead > MAX_ANALOG_READ / 2) return true;
  else return false;
}
