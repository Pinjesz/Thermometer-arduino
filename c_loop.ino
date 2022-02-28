void loop() {
  if (millis() - lastMeasurement >= measureBreak) {
    getTemperatureAndHumidity();

    updateLED();
  }

  if (soundChanged == true) {
    updateLED();
  }

  checkForButtonPress();

  checkForSound();

  getPositionsFromPotentiometer();

  getInfraredReading();

  if (change == true) {
    updateDisplay();
  }

  writeTimer();
}
