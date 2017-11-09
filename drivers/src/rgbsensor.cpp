#include "../inc/rgbsensor.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
 
}


void loop() {
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn on LED
  
  /*Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.println(blue);
  Serial.println(getColor(red,green,blue));  
  delay(500);*/

}

String getColor(int red,int green, int blue)
{
  int threshold = 200;
  int whiteThreshold = 1500;
  int cyanThreshold = 250;
  int greenThreshold = 150;
  int purpleThreshold = 500;
  String color = "none";
  
  if(((red - blue) > threshold && (red - green) > threshold))
  {
    color = "red";
  }
  if(((red - blue) < purpleThreshold && (red - green) > threshold))
  {
    color = "purple";
  }
  if(((blue - red) > threshold && (blue - green) > threshold))
  {
    color = "dark blue";
  }
  if(((green - red) > threshold && (blue - green) < cyanThreshold))
  {
    color = "cyan";
  }
  if(((green - red) > greenThreshold && (green - blue) > threshold))
  {
    color = "green";
  }
  if(((green - red) < threshold && (green - blue) > threshold))
  {
    color = "yellow";
  }
  if(red > whiteThreshold && green > whiteThreshold && blue > whiteThreshold)
  {
    color = "white";
  }
  return color;
}
