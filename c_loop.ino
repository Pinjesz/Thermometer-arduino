void loop() {

  checkTimer();

  checkForButtonPress();

  checkForSound();

  getPositionsFromPotentiometer();

  getInfraredReading();

  if (updateColorLED == true) {
    setColorLED();
  }

  if (updateDisplayLCD == true) {
    setDisplayLCD();
  }
}
