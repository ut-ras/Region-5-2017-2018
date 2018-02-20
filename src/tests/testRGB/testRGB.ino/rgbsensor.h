#ifndef rgbsensor_h
#define rgbsensor_h
#include <Wire.h>
#include "Adafruit_TCS34725.h"
//#include "Node.h"

class rgbsensor
{
  public:
  rgbsensor();
  enum Color {unknown, Green, Blue, Yellow, Magenta, Cyan, Grey, Red};
  char* colorTable[8] = {"unknown", "green", "blue", "yellow", "magenta", "cyan", "grey", "red"};
  Color getColor();
  
  private:
  Color getClosestColor(int red,int green, int blue);
  Adafruit_TCS34725 tcs;

};
#endif
