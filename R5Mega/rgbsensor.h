#include <Wire.h>
#include "Adafruit_TCS34725.h"



class rgbsensor
{
  public:
  rgbsensor();
  String getColor();
  enum Color {red, green, blue, yellow, magenta, cyan, grey, unknown};

  private:
  String getClosestColor(int red,int green, int blue);
  Adafruit_TCS34725 tcs;

};
