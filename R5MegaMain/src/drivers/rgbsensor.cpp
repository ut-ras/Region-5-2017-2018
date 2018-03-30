#include "rgbsensor.h"

rgbsensor::rgbsensor() {
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  boolean error = false;
  if (!tcs.begin()) {
    error = true;
  }
}

Color rgbsensor::getColor(){
  uint16_t clear, red, green, blue;

  //tcs.setInterrupt(false);

  delay(60);  // takes 50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);
  //tcs.setInterrupt(true);  // turn on LED

  return getClosestColor(red,green,blue);
}
Color rgbsensor::getClosestColor(int Red,int Green, int Blue)
{
  int redThreshold = 100;
  int blueThreshold = 80;
  int yellowThreshold = 100;
  int greyThreshold = 25;
  int cyanThreshold = 250;
  int greenThreshold = 150;
  int purpleThreshold = 50;
  Color color = unknown;

  if((((Red - Blue) > redThreshold) && ((Red - Green) > redThreshold)))
  {
    color = red;
  }
  if(((abs(Red - Blue) < purpleThreshold) && ((Blue - Green) > purpleThreshold)))
  {
    color = magenta;
  }
  if((((Blue - Red) > blueThreshold) && ((Blue - Green) > blueThreshold)))
  {
    color = blue;
  }
  if((((Green - Red) > cyanThreshold) && ((Blue - Green) < cyanThreshold)))
  {
    color = cyan;
  }
  if((((Green - Red) > greenThreshold) && ((Green - Blue) > greenThreshold)))
  {
    color = green;
  }
  if((((Green - Red) < yellowThreshold) && ((Green - Blue) > yellowThreshold)))
  {
    color = yellow;
  }
  if(((abs(Red - Blue) < greyThreshold) && (abs(Red - Green) < greyThreshold)))
  {
    color = grey;
  }

    Serial.print("\tR:\t"); Serial.print(Red);
    Serial.print("\tG:\t"); Serial.print(Green);
    Serial.print("\tB:\t"); Serial.println(Blue);
  return color;
}
