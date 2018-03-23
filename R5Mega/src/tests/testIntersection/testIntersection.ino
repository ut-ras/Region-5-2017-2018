#include "Node.h"
#include <Arduino.h>
#include "intersectionSensors.h"

Graph g;
intersectionSensors *sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensor = new intersectionSensors(&g, 22, 23, 24, 25, 26, 27);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Next Frame");
  //sensor->printDataRedNorth();

  Serial.println("Intersection Tests");
  //crossTest1();
  crossTest2();
  //spiralTest1();
  //spiralTest2();
  
  delay(100);
}

//set direction, print current node information, print next intersection information
void printCurrentTest(int nextDir) {
  Serial.print("Current Node: ");
  //Remove all print statements in this file except this one for gui test
  Serial.println(g.getCurrentNode()->toString());  

  if (g.getCurrentNode()->isNull()){
    Serial.println("Hit an empty node");
  } 
  else {
    //set next dir
    g.setCurrentDirection(nextDir);
    Serial.print("Set direction: ");
    Serial.println(g.getCurrentDirection());
    
    //print next intersection data
    pointlineData nextData = sensor->getNextIntersection();
    Serial.print("Next intersection expected:");
    Serial.println(sensor->PLDatatoString(nextData));

    //go to next intersection
    g.setCurrentNode(g.getNextIntersection());
  }
  Serial.println();
  delay(100);   
}

void crossTest1() {
  Serial.println("Cross Test - inside cross test\n");
  delay(1000);
  Node *endNode = g.getNode(Name::R); //so we're ending in the red corner
  
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  Serial.println();
  delay(500);

  int loopPath[38] = {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   //from green to magenta
                        6, 0, 1,                        //from magenta to cyan
                        5, 5, 5, 5, 5, 5, 5, 5, 5, 5,   //from cyan to blue
                        1, 2, 3,                        //from blue to yellow
                        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 };  //from yellow to red 
  int nextDir = 2;
  int numPathDirs = 38;

  g.setCurrentNode(g.getNode(Name::G));
  g.setCurrentDirection(nextDir);

  g.printSerial();
  
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
    if(g.getCurrentNode()->isNull()){
      Serial.println("Hit an empty node");
      break;
    } 
    printCurrentTest(loopPath[i % numPathDirs]);
  }
  
  Serial.print("Final Node: ");
  Serial.println(g.getCurrentNode()->toString()); 

  while(1);
}


void crossTest2() {
  Serial.println("Reverse Cross Test - inside reversed cross test\n");
  delay(1000);
  int loopPath[38] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  //from red to yellow
                      7, 6, 5,                        //from yellow to blue
                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   //from blue to cyan
                      5, 4, 2,                        //from cyan to magenta
                      6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };  //from magenta to green 
  int nextDir = 3;
  int numPathDirs = 38;
  Node *endNode = g.getNode(Name::G); //so we're ending in the green box
  
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  Serial.println();
  delay(500);

  g.setCurrentNode(g.getNode(Name::R));
  g.setCurrentDirection(nextDir);

  g.printSerial();
  
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
    if(g.getCurrentNode()->isNull()){
      Serial.println("Hit an empty node");
      break;
    } 
    printCurrentTest(loopPath[i % numPathDirs]);
  }
  
  Serial.print("Final Node: ");
  Serial.println(g.getCurrentNode()->toString()); 

  while(1);
}


void spiralTest1() {
  Serial.println("Spiral Test - inside spiral test\n");
  delay(1000);
  int loopPath[7] = {7, 0, 0, 6, 4, 4, 2};
  int numPathDirs = 7;
  int nextDir = 0;
  Node *endNode = g.getNode(Name::X); //so we're ending in the center
  
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  Serial.println();
  delay(500);

  g.setCurrentNode(g.getNode(Name::Y));
  g.setCurrentDirection(nextDir);
  
  g.printSerial();
    
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
    if(g.getCurrentNode()->isNull()){
      Serial.println("Hit an empty node");
      break;
    } 
    printCurrentTest(loopPath[i % numPathDirs]);
  }
  
  Serial.print("Final Node: ");
  Serial.println(g.getCurrentNode()->toString()); 
  while(1);
}



void spiralTest2() {
  Serial.println("Reverse Spiral Test - reverse spiral test\n");
  delay(1000);

  int loopPath[8] = {7, 2, 4, 4, 6, 0, 0, 2};
  int numPathDirs = 8;
  int nextDir = 7;
  Node *endNode = g.getNode(Name::R); //so we're ending in the red corner
  
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  Serial.println();
  delay(500);

  g.setCurrentNode(g.getNode(Name::X));
  g.setCurrentDirection(nextDir);

  g.printSerial();
    
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
    if(g.getCurrentNode()->isNull()){
      Serial.println("Hit an empty node");
      break;
    } 
    printCurrentTest(loopPath[i % numPathDirs]);
  }
  
  Serial.print("Final Node: ");
  Serial.println(g.getCurrentNode()->toString()); 
  while(1);
}


