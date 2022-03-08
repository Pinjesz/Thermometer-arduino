void checkTimer() {
  if (timer == TIMER_START) {
    getTemperatureAndHumidity();
  } else {
    timer = timerChanger + measureBreak - (millis() - lastMeasurement) / 1000;
    if (timer < 0) {
      timer = 0;
    }
    if (timer > 9999) {
      timer = 9999;
    }

    if (timer == 0) {
      getTemperatureAndHumidity();
    }
  }
  if (displayMode == true) {
    writeFourDigits(timer, -1);
  } else {
    updatePlace();
    writeDigitsOneByOne(timer, -1);
  }
}


void checkForButtonPress() {
  buttonReading = readAnalogToDigital(buttonPin);

  if (buttonReading == true && previousButtonReading == false) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      view = !view;
      updateDisplayLCD = true;
      lastDebounceTime = millis();
    }
  }
  previousButtonReading = buttonReading;
}

void checkForSound() {
  sound = analogRead(soundPin);

  if (sound > previousSound + soundDifference) {
    soundOn = true;
  } else {
    soundOn = false;
  }
  
  if (soundOn == true && previousSoundOn == false) {
    if ((millis() - lastSoundChange) > soundDelay) {
      lastSoundChange = millis();
      turnLightOn = !turnLightOn;
      updateColorLED = true;
    }
  }
  
  previousSoundOn = soundOn;
  previousSound = sound;
}


void getPositionsFromPotentiometer() {
  potentiometer = analogRead(potentiometerPin);
  if (view == false) {
    temporary = potentiometer / (MAX_ANALOG_READ / TEMP_POSSIBILITIES);
    tempPosition = temporary;
    if (previousTempPosition != tempPosition) {
      updateDisplayLCD = true;
      previousTempPosition = tempPosition;
    }
  } else {
    temporary = potentiometer / (MAX_ANALOG_READ / HUMI_POSSIBILITIES);
    humiPosition = temporary;
    if (previousHumiPosition != humiPosition) {
      updateDisplayLCD = true;
      previousHumiPosition = humiPosition;
    }
  }
}


void getInfraredReading() {
  if (IrReceiver.decode()) {
    if (millis() >= lastCommand + sameCommandDelay) {
      previousCommand = 0;
    }
    command = IrReceiver.decodedIRData.command;
    //    int address = IrReceiver.decodedIRData.address;
    //    int rawData = IrReceiver.decodedIRData.decodedRawData;

    if ((command != 0) && (command != previousCommand)) {
      executeCommand();
      lastCommand = millis();
      previousCommand = command;
    }
    IrReceiver.resume();
  }
}


void setColorLED() {
  updateColorLED = false;
  if (turnLightOn == true) {
    if (t >= 17.5 && t < 25) { // good temperature
      setRGB(GREEN);
    }
    else if ((t >= 25 && t < 30) || (t >= 15 && t < 17.5)) { // medium temperature
      setRGB(ORANGE);
    }
    else if ((t >= 30) || (t < 15)) { // bad temperature
      setRGB(RED);
    }
  }
  else {
    setRGB(BLACK);
  }
}


void setDisplayLCD() {
  updateDisplayLCD = false;
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
}
