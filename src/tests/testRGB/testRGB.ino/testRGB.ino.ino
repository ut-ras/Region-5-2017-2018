#include <Arduino.h>
#include "rgbsensor.h"
#include "testRGB.cpp"
//#include "Node.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupRGBTest();
}

void loop() {
  // put your main code here, to run repeatedly:
  loopRGBTest();
}
