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

void Graph::graphTest() {
  
  Serial.println("Graph Test - inside graph test\n");
  delay(1000);

  Graph g;
  g.printSerial();

  Node *endNode = g.getNode(Name::X); //so we're ending in the center
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  delay(500);

  int loopPath[8] = {7, 0, 0, 6, 4, 4, 2, 2};
  int numPathDirs = 8;
  int nextDir = 0;

  g.setCurrentNode(getNode(Name::Y));
  g.setCurrentDirection(7);
  Node *nextNode;
  
  for(int i=0; g.getCurrentNode()->g.getName() != endNode->g.getName(); i++) {
    Serial.print("Current Node: ");

    //Remove all print statements in this file except this one for gui test
    Serial.println(g.getCurrentNode()->toString());
    Serial.print("Current direction: ");
    Serial.println(g.getCurrentDirection());    

    if(g.getCurrentNode()->isNull()){
      Serial.println("Hit an empty node");
      break;
    } 
    else {
      nextDir = loopPath[i % numPathDirs];
      g.setCurrentDirection(nextDir);

      //grab next intersection data and print it out
      pointlineData nextData = sensor->getNextIntersection();
      Serial.println(nextData.toString());
      nextNode = g.getNeighbor(g.getCurrentNode(), nextDir);
      g.setCurrentNode(nextNode);
  
      Serial.print("Moved in direction: ");
      Serial.println(g.getCurrentDirection());
    }
    
    delay(500);
  }
  
  Serial.print("Final Node: ");
  Serial.println(g.getCurrentNode()->toString()); 

  while(1);
}
