#include <Time.h>
#include <Arduino.h>

#include "src/control/tokenControl.h"
#include "src/control/driveControl.h"
#include "src/control/Graph.h"

/* Required libraries (sketch/include library/manage libraries to add)
 * Adafruit_TCS34725
 */

#define FWD true;

tokenControl *tokenController;
driveControl *driveController;
Graph * mapGraph;

void setup() {
  // put your setup code here, to run once:]
  Serial.begin(9600);

  mapGraph = new Graph();
  tokenController = new tokenControl(mapGraph);
  driveController = new driveControl(mapGraph);

  Wire.begin();

  //testTokenControl();
  testDriveControl();
  //printIntersectionData();
}


void loop() {
  // put your main code here, to run repeatedly:

}

void testTokenControl() {
  Blink();
  //tokenController->goToEveryColour();
  tokenController->depositTokens(magenta);
  while(1);
}

void Blink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void testDriveControl() {
  driveController->move(true);

  //driveController->setCurrentLocationForTest(R5, 4);   //where the bot is starting, (location, dir)
  //driveController->forwardToIntersection();
}

void printIntersectionData() {
  intersectionSensors * s = driveController->getIntersectionSensors();
  while(1) {
    Serial.println(s->getData().toString());
    delay(500);
  }
}

/*
void round1() {
	int[] inventory = new int[6];
  time_t t = now();

  //get to y1 box:
  driveController->forwardToIntersection();
  driveController->turnTo(2);
  driveController->forwardToIntersection();

  //collect across diagonal going from yellow to red
  driveController->turnTo(7);
	for(int i = 0; i < 4; i++){
		driveController->forwardToIntersection();
		tokenController->pickUpToken();
    //Map will update in the background
	}

  //Cross grey box
	driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //Continue to r1
	for(int i = 0; i < 4; i++){
		driveController->forwardToIntersection();
		tokenController->pickUpToken();
	}
  if(mapGraph->getNumTokens(red) == 2){
    //drop off red tokens on way by
    driveController->turnTo(7);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(red);
    driveController->turnTo(3);
    driveController->forwardToIntersection();

  }

  //go to g1
  driveController->turnTo(4);               //turn 135 deg left
  driveController->forwardToIntersection();
  tokenController->pickUpToken();
  if(mapGraph->getNumTokens(green) == 2){
    //drop off green tokens on way by
    driveController->turnTo(6);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(green);
    driveController->turnTo(2);
    driveController->forwardToIntersection();
  }

  //go across to m1
  driverControl->turnTo(2);
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //cross grey box
  driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //continue to m1
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }
  if(mapGraph->getNumTokens(magenta) == 2){
    //drop off magenta tokens on way by
    driveController->turnTo(2);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(magenta);
    driveController->turnTo(6);
    driveController->forwardToIntersection();
  }

  //go to c1
  driveController->turnTo(0);
  driveController->forwardToIntersection();
  tokenController->pickUpToken();
  if(mapGraph->getNumTokens(cyan) == 2){
    //drop off cyan tokens on way by
    driveController->turnTo(1);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(cyan);
    driveController->turnTo(5);
    driveController->forwardToIntersection();
  }

  //go across the diagonal from cyan to blue (b1)
  driveController->turnTo(5);
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //cross grey box
  driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //continue to blue box
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //---------------------------------------------------
  //           DROP OFF PHASE

  if(mapGraph->getNumTokens(blue) > 0){
    //drop off blue tokens
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(blue);

    //get back to b1
    driveController->turnTo(1);
    driveController->forwardToIntersection();
  }

  //go to g1
  driveController->turnTo(0);
  driveController->forwardToIntersection();

  if(mapGraph->getNumTokens(green) > 0){
    //drop off green tokens
    driveController->turnTo(6);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(green);

    //get back to g1
    driveController->turnTo(2);
    driveController->forwardToIntersection();
  }

  //go to r1
  driveController->turnTo(0);
  driveController->forwardToIntersection();

  if(mapGraph->getNumTokens(red) > 0){
    //drop off red tokens
    driveController->turnTo(7);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(red);

    //get back to r1
    driveController->turnTo(3);
    driveController->forwardToIntersection();
  }

  //go to c1
  driveController->turnTo(2);
  driveController->forwardToIntersection();
  driveController->turnTo(1);

  if(mapGraph->getNumTokens(cyan) > 0){
    //drop off cyan tokens
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(cyan);

    //get back to c1
    driveController->turnTo(5);
    driveController->forwardToIntersection();
  }

  //go to magenta
  driveController->turnTo(4);
  driveController->forwardToIntersection();

  if(mapGraph->getNumTokens(magenta) > 0){
    //drop off magenta tokens
    driveController->turnTo(2);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(magenta);

    //get back to m1
    driveController->turnTo(6);
    driveController->forwardToIntersection();
  }

  //go to yellow box
  driveController->turnTo(4);
  driveController->forwardToIntersection();

  if(mapGraph->getNumTokens(yellow) > 0){
    //drop off yellow tokens
    driveController->turnTo(3);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(yellow);
  }

  //go to the white box
  driveController->turnTo(6);
  driveController->forwardToIntersection();


  //---------------------------------------------------
  //Pseudo code for drop off phase
  //check if enough time

    //if so, drop tokens to blue and red
    //check if enough time,
      //if so, drop tokens to cyan
          //
      //if not, go to white box

  //else, not enough time
    //go to white box


}

*/

/*
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
*/
