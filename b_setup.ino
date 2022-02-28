void setup() {

  // setup the pins
  pinMode(dataDisplayPin, OUTPUT);digitalWrite(dataDisplayPin, 0); 
  pinMode(showDisplayPin, OUTPUT);digitalWrite(showDisplayPin, 0); 
  pinMode(clockDisplayPin, OUTPUT);digitalWrite(clockDisplayPin, 0); 
  for (auto pinNumber:digits) {
    pinMode(pinNumber, OUTPUT);digitalWrite(pinNumber, 1); // high for 7-segment display (timer)
  }
  // PWM for LED
  pinMode(redPin, OUTPUT);analogWrite(redPin, 0);
  pinMode(greenPin, OUTPUT);analogWrite(greenPin, 0);
  pinMode(bluePin, OUTPUT);analogWrite(bluePin, 0);
  // sensors
  pinMode(temperaturePin, INPUT);
  pinMode(infraredPin, INPUT);
  
  Serial.begin(BAUD_RATE);
  Serial.println(F("Start termometra"));


  // start the thermometer
  dht.begin();
  lastMeasurement = - measureBreak;


  // setup button debouncing
  previousButtonReading = false;
  buttonReading = false;
  lastDebounceTime = 0;


  // setup the lcd
  lcd.init();
  lcd.clear();
  lcd.backlight();


  // create chars for lcd
  lcd.createChar(0, si);
  lcd.createChar(1, ci);
  lcd.createChar(2, degree);


  // read value from potentiometer
  potentiometer = analogRead(potentiometerPin);

  // setup the sound
  soundOn = false;
  previousSoundOn = false;
  turnLightOn = true;
  sound = 0;
  lastSoundChange = false;
  soundChanged = false;
  previousSound = 100;


  // set help variables
  view = false;
  change = true;


  // get position for temperature
  temporary = potentiometer / (POTENTIOMETER_RANGE / TEMP_POSSIBILITIES);
  tempPosition = temporary;
  previousTempPosition = temporary;


  // get position for humidity
  temporary = potentiometer / (POTENTIOMETER_RANGE / HUMI_POSSIBILITIES);
  humiPosition = temporary;
  previousHumiPosition = temporary;


  // infrared
  IrReceiver.begin(infraredPin, ENABLE_LED_FEEDBACK);


  // start value for the timer
  timer = measureBreak/1000;
}
