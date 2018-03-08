#include "Node.h"
#include <Arduino.h>
#include "intersectionSensors.h"
Graph* g;
intersectionSensors *sensor;
void setup() {
  // put your setup code here, to run once:
  g = new Graph();\
  sensor = new intersectionSensors(*g, 22, 23, 24, 25, 26, 27);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello");
  intersectionSensors::pointlineData data = sensor->getData();
  Serial.println(data.l0);
  Serial.println(data.l1);
    Serial.println(data.l2);
  Serial.println(data.r0);
  Serial.println(data.r1);
  Serial.println(data.r2);


}
