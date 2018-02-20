#include <Time.h>
#include <Arduino.h>
#include "Graph.h"
#include "Node.h"


Graph* g;


void setup() {
  // put your setup code here, to run once:
  //setupMotorsTest();
  setupGraphTest();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //loopMotorsTest();
  loopGraphTest();
}

void setupGraphTest() {
  g = new Graph();
  g->setCurrentNode(g->getNode(Name::Y1));
  g->setCurrentDirection(0);
}

void loopGraphTest() {

  Serial.println(g->getCurrentNode()->toString());
  Serial.println(g->getNeighbor(g->getCurrentNode(), 0)->toString());
  while(1);
}
