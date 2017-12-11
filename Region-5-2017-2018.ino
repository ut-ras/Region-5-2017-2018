#include "motorController.h"
#include "rgbsensor.h"
#include "tokenControl.h"
#include "intersectionSensors.h"
#include <Time.h>
#include <Arduino.h>
#include "drivers/inc/*"
#include "control/inc/*"
#include "test/*"


void setup() {
  // put your setup code here, to run once:
setupMotorsTest();
}	

void loop() {
  // put your main code here, to run repeatedly:


	loopMotorsTest();

}

void round1(){
	int[] inventory = new int[6];
  time_t t = now();
	if(whichSide() == Node::Color::yellow){
  //Collection
		turn(PI / 4);
   //collect across diagonal going from yellow to red
		for(int i = 0; i < 4; i++){
			forwardToIntersection();
			pickUpToken();
			updateInventory(storeToken(), inventory);
		}
		moveForward(distance across grey square);
		for(int i = 0; i < 4; i++){
			forwardToIntersection();
			pickUpToken();
			updateInventory(storeToken(), inventory);
		}
		depositIfEnough(Node::Color::red, 3, inventory[0]);
   //go to green
    turn(3 * PI / 4);
    forwardToIntersection();
    depositIfEnough(Node::Color::green, 3, inventory[1]);
    //go across to magenta
    turn(PI / 2);
    for(int i = 0; i < 4; i++){
      forwardToIntersection();
      pickUpToken();
      updateInventory(storeToken(), inventory);
    }
    moveForward(distance across grey square);
    for(int i = 0; i < 4; i++){
      forwardToIntersection();
      pickUpToken();
      updateInventory(storeToken(), inventory);
    }
    depositIfEnough(Node::Color::magenta, 3, inventory[4]);
    turn(PI/2);
    forwardToIntersection();
    depositIfEnough(Node::Color::cyan, 3, inventory[5]);
    //go across the diagonal from cyan to blue
    turn(3 * PI / 4);
    for(int i = 0; i < 4; i++){
      forwardToIntersection();
      pickUpToken();
      updateInventory(storeToken(), inventory);
    }
    moveForward(distance across grey square);
    for(int i = 0; i < 4; i++){
      forwardToIntersection();
      pickUpToken();
      updateInventory(storeToken(), inventory);
    }
    depositIfEnough(Node::Color::blue, 3, inventory[2]);
    //---------------------------------------------------
    


	} else{ // first color is red
  

	}
}

void round2(){
	int[] inventory = new int[6];
}

void round3(){
	int[] inventory = new int[7];
}

void forwardToIntersection(){
	while(getData() != getNextIntersection())
		moveForward();
}

void updateInventory(Node::Color c, int[] inventory){
  inventory[c]++;
}

void depositIfEnough(Node::Color c, int min, int current){
	if(current >= min)
		tokenControl::depositTokens();
}

Node::Color whichSide(){
	moveForward(distance to colored square);
	return getColor();
}
