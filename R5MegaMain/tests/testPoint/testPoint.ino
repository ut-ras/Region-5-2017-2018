#include <Arduino.h>
#include <Time.h>
#include "src/pointline.h"

pointline *point;
pointline *point2;
void setup() {  
    // put your setup code here, to run once:]
    Serial.begin(9600);
    //setupGraphTest();
    point = new pointline(27);
    //point2 = new pointline(22); 
  //  setupTestArrayLine();
    }
void loop() {
  // put your main code here, to run repeatedly:
  //loopArrayLineTest();
  Serial.print(point->getValue());
  //Serial.print(point2->getValue());
  Serial.println();
  //loopGraphTest();

}
