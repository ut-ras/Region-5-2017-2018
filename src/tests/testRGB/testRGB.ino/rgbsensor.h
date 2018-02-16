#include <Wire.h>
#include "rgbsensor.h"
#include "Adafruit_TCS34725.h"
#include <Arduino.h>
//#include "Node.h"

class rgbsensor
{
  public:
  rgbsensor();
  Color getColor();
  
  private:
  Color getClosestColor(int red,int green, int blue);
  Adafruit_TCS34725 tcs;

};
