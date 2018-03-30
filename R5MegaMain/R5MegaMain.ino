#include <Time.h>
#include <Arduino.h>

#include "src/control/tokenControl.h"
#include "src/control/driveControl.h"
#include "src/control/Graph.h"

/* Required libraries (sketch/include library/manage libraries to add)
 * Adafruit_TCS34725
 */

tokenControl *tokenController;
driveControl *driveController;
Graph * mapGraph;

void setup() {
  // put your setup code here, to run once:]
  Serial.begin(9600);

  mapGraph = new Graph();
  tokenController = new tokenControl(mapGraph);
  driveController = new driveControl(mapGraph);

  testTokenControl();
  //testDriveControl();
}


void loop() {
  // put your main code here, to run repeatedly:

}

void testTokenControl() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  tokenController->pickUpToken();
  while(1);
}

void testDriveControl() {
  driveController->move(2);

  //driveController->setCurrentLocationForTest(R1, 0);   //where the bot is starting, (location, dir)
  //driveController->forwardToIntersection();
  while(1);
}

/*
void round1() {
	int[] inventory = new int[6];
  time_t t = now();

  turn(PI / 4);

  //collect across diagonal going from yellow to red
	for(int i = 0; i < 4; i++){
		driveController->forwardToIntersection();
		tokenController->pickUpToken();
    //Map will update in the background
	}

  //Cross grey box
	driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //Continue to red box
	for(int i = 0; i < 4; i++){
		driveController->forwardToIntersection();
		tokenController->pickUpToken();
	}

  //go to green
  driveController->turn45(3 * PI / 4);  //turn 135 deg left
  driveController->forwardToIntersection();
  
  //go across to magenta
  turn(PI / 2);
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //cross grey box
  driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //continue to magenta
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //go to cyan
  turn(PI/2);
  forwardToIntersection();

  //go across the diagonal from cyan to blue
  turn(3 * PI / 4);
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

  //drop off blue tokens
  driveController->forwardToIntersection();
  move(FWD);
  delay(1000);
  stop();
  tokenController->depositTokens(blue);
  turn45();
  turn45();
  turn45();
  turn45();

  //get back to b1
  driveController->forwardToIntersection();
  turn45();

  //go to green
  driveController->forwardToIntersection();
  turn45();
  turn45();

  //drop off green tokens
  driveController->forwardToIntersection();
  move(FWD);
  delay(1000);
  stop();
  tokenController->depositTokens(green);
  turn45();
  turn45();
  turn45();
  turn45();

  //get back to g1
  driveController->forwardToIntersection();
  turn45();
  turn45();

  //go to red
  driveController->forwardToIntersection();
  turn45();

  //drop off red tokens
  driveController->forwardToIntersection();
  move(FWD);
  delay(1000);
  stop();
  tokenController->depositTokens(red);
  turn45();
  turn45();
  turn45();
  turn45();

  //if no time, get in white box

  //get back to r1
  driveController->forwardToIntersection();
  turn45();

  //go to cyan
  driveController->forwardToIntersection();
  turn45();

  //drop off red tokens
  driveController->forwardToIntersection();
  move(FWD);
  delay(1000);
  stop();
  tokenController->depositTokens(cyan);
  turn45();
  turn45();
  turn45();
  turn45();

  //get back to c1
  driveController->forwardToIntersection();
  turn45();

  //go to magenta
  driveController->forwardToIntersection();
  turn45();
  turn45();

  //drop off magenta tokens
  driveController->forwardToIntersection();
  move(FWD);
  delay(1000);
  stop();
  tokenController->depositTokens(magenta);
  turn45();
  turn45();
  turn45();
  turn45();

  //get back to m1
  driveController->forwardToIntersection();
  turn45();
  turn45();

  //go to yellow
  driveController->forwardToIntersection();
  turn45();

  //drop off yellow tokens
  driveController->forwardToIntersection();
  move(FWD);
  delay(1000);
  stop();
  tokenController->depositTokens(red);

  //go to the white box
  turn45();
  turn45();
  turn45();
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
