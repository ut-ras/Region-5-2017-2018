#include "Node.h"
#include <Arduino.h>
#include "intersectionSensors.h"
Graph* g;
intersectionSensors *sensor;
void setup() {
  // put your setup code here, to run once:
  g = new Graph();
  Serial.begin(9600);
  sensor = new intersectionSensors(*g, 22, 23, 24, 25, 26, 27);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Next Frame");
  sensor->printDataRedNorth();
  delay(100);


}
