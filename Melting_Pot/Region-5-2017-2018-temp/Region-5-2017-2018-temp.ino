#include <Time.h>
#include <Arduino.h>
#include "Graph.h"
#include "Node.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Graph Test - setup");

}

void loop() {
  Graph * g = new Graph();
  Serial.println("Graph Test - main loop");
  g->graphTest();
}
