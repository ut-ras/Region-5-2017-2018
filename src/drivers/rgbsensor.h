#include <Wire.h>
#include "Adafruit_TCS34725.h"

class rgbsensor
{
  public:
  rgbsensor();
  String getColor();

  private:
  String getClosestColor(int red,int green, int blue);
  Adafruit_TCS34725 tcs;

};
