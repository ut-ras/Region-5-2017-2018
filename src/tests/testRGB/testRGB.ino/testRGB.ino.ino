#include <Arduino.h>
#include "rgbsensor.h"
//#include "Node.h"
rgbsensor* rgb;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Color View Test!");

  rgb = new rgbsensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  // put your main code here, to run repeatedly:
  Serial.println(rgb->colorTable[rgb->getColor()]);

  /*Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.println(blue);
  Serial.println(getColor(red,green,blue));
  delay(500);*/
}
