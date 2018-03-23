#ifndef rgbsensor_h
#define rgbsensor_h
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "Node.h"

class rgbsensor
{
  public:
  rgbsensor();
  char* colorTable[9] = {"unknown", "green", "blue", "yellow", "magenta", "cyan", "grey", "red", "black"};
  Color getColor();
  
  private:
  Color getClosestColor(int red,int green, int blue);
  Adafruit_TCS34725 tcs;

};
#endif
