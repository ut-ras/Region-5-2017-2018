#include <Time.h>
#include <Arduino.h>
#include "Graph.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Graph Test - setup");
  delay(1000);
}

void loop() {
  Serial.println("Graph Test - main loop");
  delay(1000);
  
  Graph g;
  g.printRawGraph();
  g.graphTest();
  
  delay(60000);
}
  
