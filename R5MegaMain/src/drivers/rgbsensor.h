#ifndef rgbsensor_h
#define rgbsensor_h
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "../control/Node.h"
#include "../control/RunningMedian.h"

class rgbsensor
{
  public:
  rgbsensor();
  char* colorTable[8] = {"red", "green", "blue", "yellow", "magenta", "cyan", "grey", "unknown"};
  Color getColor();
  Color colorTester();

  private:
  Color getColorHelper();
  Color getClosestColor(int red,int green, int blue);
  Adafruit_TCS34725 tcs;

};
#endif
