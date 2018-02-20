#include "rgbsensor.h"
rgbsensor::rgbsensor() {
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  boolean error = false;
  if (!tcs.begin()) {
    error = true;
  }
}

rgbsensor::Color rgbsensor::getColor(){
  uint16_t clear, red, green, blue;
  
  tcs.setInterrupt(false);
  
  delay(60);  // takes 50ms to read
   tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn on LED

  return getClosestColor(red,green,blue);
}
rgbsensor::Color rgbsensor::getClosestColor(int red,int green, int blue)
{
  int threshold = 200;
  int whiteThreshold = 1500;
  int cyanThreshold = 250;
  int greenThreshold = 150;
  int purpleThreshold = 500;
  Color color = unknown;

  if(((red - blue) > threshold && (red - green) > threshold))
  {
    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.println(blue);
    color = Red;
  }
  if(((red - blue) < purpleThreshold && (red - green) > threshold))
  {
    color = Magenta;
  }
  if(((blue - red) > threshold && (blue - green) > threshold))
  {
    color = Blue;
  }
  if(((green - red) > threshold && (blue - green) < cyanThreshold))
  {
    color = Cyan;
  }
  if(((green - red) > greenThreshold && (green - blue) > threshold))
  {
    color = Green;
  }
  if(((green - red) < threshold && (green - blue) > threshold))
  {
    color = Yellow;
  }
  if(red > whiteThreshold && green > whiteThreshold && blue > whiteThreshold)
  {
    color = Grey;
  }
  return color;
}
