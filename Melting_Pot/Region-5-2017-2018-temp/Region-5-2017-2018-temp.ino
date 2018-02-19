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
  g->setCurrentNode(g->getNode(Name::Y));
  g->setCurrentDirection(0);
}

void loopGraphTest() {

  //Serial.println("Current Node is: " + g->getCurrentNode() + "\nCurrent Direction is: " + g->getCurrentDirection());
  if(g->getNeighbor(g->getCurrentNode(), 0)->getName() ==  Name::M) {
    //Serial.println("Get neighbor test 1 passed");
  }
  else {
    //Serial.println("Get neighbor test 1 failed");
  }
}
