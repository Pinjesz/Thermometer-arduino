#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

#define BAUD_RATE 9600
#define MAX_ANALOG_READ 1024

long lastMeasurement;
const unsigned long measureBreak = 30; // reading every 30 seconds
#define TIMER_START -1
int timer;
int timerChanger;
float t;
int h;
char buff[55];
char t_str[4];

#define potentiometerPin A1
#define TEMP_POSSIBILITIES 9.0
#define HUMI_POSSIBILITIES 11.0
int potentiometer;
int tempPosition;
int humiPosition;
int previousTempPosition;
int previousHumiPosition;
bool view;
bool updateDisplayLCD;
float temporary;

#define dataDisplayPin 2
#define showDisplayPin 3
#define clockDisplayPin 4
int digits[4] = {5, 6, 7, 8};
bool displayZeros;
int numbers[4];
int place;
bool displayMode;
int displayDelay;

#define buttonPin A3
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

#define soundPin A2
bool soundOn;
bool previousSoundOn;
bool turnLightOn;
int sound;
bool lastSoundChange;
const unsigned soundDelay = 100;
bool updateColorLED;
float previousSound;
const unsigned soundDifference = 10;

#define infraredPin 13
int command;
int previousCommand;
const unsigned sameCommandDelay = 200;
long lastCommand;

#define BUTTON_CHminus 69
#define BUTTON_CH 70
#define BUTTON_CHplus 71
#define BUTTON_PREV 68
#define BUTTON_NEXT 64
#define BUTTON_PLAY 67
#define BUTTON_VOLminus 7
#define BUTTON_VOLplus 21
#define BUTTON_EQ 9
#define BUTTON_0 22
#define BUTTON_100 25
#define BUTTON_200 13
#define BUTTON_1 12
#define BUTTON_2 24
#define BUTTON_3 94
#define BUTTON_4 8
#define BUTTON_5 28
#define BUTTON_6 90
#define BUTTON_7 66
#define BUTTON_8 82
#define BUTTON_9 74

#define lightPin A0
int light;
