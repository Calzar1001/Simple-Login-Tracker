/****************
  Login Tracker Hardware
  Ver 1.0
  Reads Distance and light
  displays with OLED
  and writes to SERIAL
 ****************/
//OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Analog
int lastLdrVal;

int lastDistVal;

//Digital
const int ledPin = 11;
boolean ledState;
int lightVal;

//Time
//!Be Careful Overflow! -- look into soloutions
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 2000;           // interval at which to blink (milliseconds)


void setup()
{

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  Serial.begin(9600);
  //Led digital pin Setup
  pinMode(ledPin, OUTPUT);



}

void loop()
{
  unsigned long currentMillis = millis();
  display.clearDisplay();

  int ldrValue = analogRead(A6);
  int distSense = analogRead(A0);

  if (ldrValue != lastLdrVal && distSense != lastDistVal )
  {
    Serial.print("Light Level: ");
    Serial.print(ldrValue);
    Serial.print("\t");
    lastLdrVal = ldrValue;
    Serial.print("Distance: ");
    Serial.println(distSense);
    lastDistVal = distSense;
  }

  
  /*
    //LED LIGHT LEVEL
    lightVal = map(distSense, 0, 1023, 255, 0);
    analogWrite(ledPin, distSense / 4);
  */

  ///OLED DISPLAY
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text

  display.setCursor(0, 0);
  display.print("Light Level: ");
  display.print(ldrValue);

  display.setCursor(0, 10);
  display.print("Distance: ");
  display.print(distSense);

  display.display();
  delay(10);
  //

  //LED BLINK
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
    {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    if (ledState == HIGH) {
      //LED LIGHT LEVEL
      lightVal = map(ldrValue, 340, 750, 0, 255);
      analogWrite(ledPin, lightVal);
    } else {
      analogWrite(ledPin, 0);

    }
  }


  
}
