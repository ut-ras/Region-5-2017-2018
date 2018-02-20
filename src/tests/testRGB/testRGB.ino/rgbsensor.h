#ifndef rgbsensor_h
#define rgbsensor_h
#include <Wire.h>
#include "Adafruit_TCS34725.h"
//#include "Node.h"

class rgbsensor
{
  public:
  rgbsensor();
  enum Color {red, green, blue, yellow, magenta, cyan, grey, unknown};
  Color getColor();
  
  private:
  Color getClosestColor(int red,int green, int blue);
  Adafruit_TCS34725 tcs;

};
#endif
