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
	if(whichSide() == Node::Color::yellow){
		turn(PI / 4);
		for(int i = 0; i < 4; i++){
			forwardToIntersection();
			pickUpToken();
			updateInventory(storeToken());
		}
		moveForward(distance across grey square);
		for(int i = 0; i < 4; i++){
			forwardToIntersection();
			pickUpToken();
			updateInventory(storeToken());
		}
		depositIfEnough("red");



	} else{

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

void depositIfEnough(Node::Color c, int min, int current){
	if(current >= min)
		tokenControl::depositTokens();

}

Node::Color whichSide(){
	moveForward(distance to colored square);
	return getColor();
}
