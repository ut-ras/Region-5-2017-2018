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
  crossTest1();
  //crossTest2();
  //spiralTest1();
  //spiralTest2();
  
  delay(100);
}


void crossTest1() {
  
  Serial.println("Cross Test - inside cross test\n");
  delay(1000);

  //g.printSerial();

  Node *endNode = g.getNode(Name::R); //so we're ending in the red corner
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  delay(500);

  int loopPath[38] = {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   //from green to magenta
                        6, 0, 1,                        //from magenta to cyan
                        5, 5, 5, 5, 5, 5, 5, 5, 5, 5,   //from cyan to blue
                        1, 2, 3,                        //from blue to yellow
                        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 };  //from yellow to red 
  int nextDir = 2;

  g.setCurrentNode(g.getNode(Name::G));
  g.setCurrentDirection(nextDir);
  Node *nextNode;
  
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
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
      nextDir = loopPath[i];
      g.setCurrentDirection(nextDir);

      //grab next intersection data and print it out
      pointlineData nextData = sensor->getNextIntersection();
      Serial.print("Next intersection expected:");
      Serial.println(sensor->PLDatatoString(nextData));
      nextNode = g.getNeighbor(g.getCurrentNode(), nextDir);
      g.setCurrentNode(nextNode);
  
      Serial.print("Moved in direction: ");
      Serial.println(g.getCurrentDirection());
    }
    
    delay(100);
  }
  
  Serial.print("Final Node: ");
  Serial.println(g.getCurrentNode()->toString()); 

  while(1);
}


void crossTest2() {
  
  Serial.println("Reverse Cross Test - inside reversed cross test\n");
  delay(1000);

  g.printSerial();

  Node *endNode = g.getNode(Name::G); //so we're ending in the green box
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  delay(500);

  int loopPath[36] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  //from red to yellow
                      7, 6, 5,                        //from yellow to blue
                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   //from blue to cyan
                      5, 4, 2,                        //from cyan to magenta
                      6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };  //from magenta to green 
  int nextDir = 3;

  g.setCurrentNode(g.getNode(Name::R));
  g.setCurrentDirection(nextDir);
  Node *nextNode;
  
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
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
      nextDir = loopPath[i];
      g.setCurrentDirection(nextDir);

      //grab next intersection data and print it out
      pointlineData nextData = sensor->getNextIntersection();
      Serial.print("Next intersection expected:");
      Serial.println(sensor->PLDatatoString(nextData));
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


void spiralTest1() {
  
  Serial.println("Spiral Test - inside spiral test\n");
  delay(1000);

  g.printSerial();

  Node *endNode = g.getNode(Name::X); //so we're ending in the center
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  delay(500);

  int loopPath[7] = {7, 0, 0, 6, 4, 4, 2};
  int numPathDirs = 7;
  int nextDir = 0;

  g.setCurrentNode(g.getNode(Name::Y));
  g.setCurrentDirection(nextDir);
  Node *nextNode;
  
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
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
      Serial.print("Next intersection expected:");
      Serial.println(sensor->PLDatatoString(nextData));
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



void spiralTest2() {
  
  Serial.println("Reverse Spiral Test - reverse spiral test\n");
  delay(1000);

  g.printSerial();

  Node *endNode = g.getNode(Name::R); //so we're ending in the red corner
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  delay(500);

  int loopPath[8] = {7, 2, 4, 4, 6, 0, 0, 2};
  int numPathDirs = 8;
  int nextDir = 7;

  g.setCurrentNode(g.getNode(Name::X));
  g.setCurrentDirection(nextDir);
  Node *nextNode;
  
  for(int i=0; g.getCurrentNode()->getName() != endNode->getName(); i++) {
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
      Serial.print("Next intersection expected:");
      Serial.println(sensor->PLDatatoString(nextData));
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
