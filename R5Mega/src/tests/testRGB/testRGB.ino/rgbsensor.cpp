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
Color rgbsensor::getClosestColor(int red,int green, int blue)
{
  int threshold = 200;
  int greyThreshold = 50;
  int cyanThreshold = 250;
  int greenThreshold = 150;
  int purpleThreshold = 500;
  Color color = unknown;

  if(((red - blue) > threshold && (red - green) > threshold))
  {
    color = red;
  }
  if(((red - blue) < purpleThreshold && (red - green) > threshold))
  {
    color = magenta;
  }
  if(((blue - red) > threshold && (blue - green) > threshold))
  {
    color = blue;
  }
  if(((green - red) > threshold && (blue - green) < cyanThreshold))
  {
    color = cyan;
  }
  if(((green - red) > greenThreshold && (green - blue) > threshold))
  {
    color = green;
  }
  if(((green - red) < threshold && (green - blue) > threshold))
  {
    color = yellow;
  }
  if(((red - blue) < greyThreshold && (red - green) < greyThreshold))
  {
    color = grey;
  }

    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.println(blue);
  return color;
}
