#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

signed long lastMeasurement;
const unsigned long measureBreak = 30000; // reading every 30 seconds
float t;
float h;
float f;

#define potentiometerPin A0
#define POTENTIOMETER_RANGE 1024.0
#define TEMP_POSSIBILITIES 9.0
#define HUMI_POSSIBILITIES 11.0
int potentiometer;
int tempPosition;
int humiPosition;
int previousTempPosition;
int previousHumiPosition;
bool view;
bool change;
float temporary;

#define dataDisplayPin 2
#define showDisplayPin 3
#define clockDisplayPin 4
int digits[4] = {5, 6, 7, 8};
unsigned long timer;

#define buttonPin A2
bool previousButtonReading;
bool buttonReading;
unsigned long lastDebounceTime;
const unsigned debounceDelay = 50;

#define temperaturePin 12     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(temperaturePin, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define ORANGE 0xFF3500
#define GREEN 0x00FF00
#define BLACK 0x000000

#define redPin 9
#define greenPin 10
#define bluePin 11

#define soundPin A1
bool soundOn;
bool previousSoundOn;
bool turnLightOn;
int sound;
bool lastSoundChange;
const unsigned soundDelay = 100;
bool soundChanged;
float previousSound;
const unsigned soundDifference = 4;

#define infraredPin 13

#define BAUD_RATE 9600
