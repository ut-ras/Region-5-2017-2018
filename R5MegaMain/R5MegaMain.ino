#include <Time.h>
#include <Arduino.h>

#include "src/control/tokenControl.h"
#include "src/control/driveControl.h"
#include "src/control/Graph.h"

/* Required libraries (sketch/include library/manage libraries to add)
 * Adafruit_TCS34725
 */

#define FWD true

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

  //mapGraph->printSerial();

  delay(2000);
  testTokenControl();
  //printIntersectionData();
  //testDriveControl();

}


void loop() {
  // put your main code here, to run repeatedly:
  Blink();
}

//debugging gui
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    int8_t inChar = Serial.parseInt();
    if ((inChar >= 0) && (inChar <= STOP)) {
      driveController->sendCommand(inChar);
    }
  }
}

void testTokenControl() {
  Blink();
  //tokenController->goToEveryColour();
  //tokenController->depositTokens(magenta);
    Serial.println("Start");
    //tokenController->readColour();
    //tokenController->pickUpToken(); 
    //Serial.println("----");
    //Serial.println("");
    delay(2000);
    while(1){
    //tokenController->readColour();
    //tokenController->pickUpToken(); 
    tokenController->pickUpToken(); 
    Serial.println("----");
    Serial.println("");
    delay(5000);
    }
}
      
void Blink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void testDriveControl() {
  //driveController->move(true);

  setCurrentLocationForTest(R5, 4);  
  Serial.println(mapGraph->getCurrentNode()->toString());
  driveController->forwardToIntersection();
  Serial.println(mapGraph->getCurrentNode()->toString());
  delay(3000);
  driveController->forwardToIntersection();
  Serial.println(mapGraph->getCurrentNode()->toString());
  delay(3000);
  driveController->turn45(true, 2);
  
}

//where the bot is starting, (location, dir)
void setCurrentLocationForTest(int name, int dir) {
  mapGraph->setCurrentNode(mapGraph->getNode(name));
  mapGraph->setCurrentDirection(dir);
  Serial.println("set node to " + String(mapGraph->getNode(name)->toString())+ " set direction to " + String(mapGraph->getCurrentDirection()));
}

void printIntersectionData() {
  intersectionSensors * s = driveController->getIntersectionSensors();
  while(1) {
    Serial.println(s->getData().toString());
    delay(500);
  }
}

/*
 * Coded by Catherine, Colton
 * Commented code with "//" - is asumming we do not need
 *                            but might need in the future
 * CHECK delay(1000) - is this the correct parameters?
 *                     delay is there for the robot to move
 *                       inside the colored box
 */
 /*
void round3() {
	int inventory[6];
  time_t startTime = second();
  time_t endTime = 480 + startTime; //time for 8 seconds


  //Start at yellow box
  //assuming it is align with the y1 box:
  driveController->forwardToIntersection();
 /// driv6eController->turn45();
  driveController->forwardToIntersection();

  //collect across diagonal going from yellow to red
	for(int i = 0; i < 4; i++){
		driveController->forwardToIntersection();
		tokenController->pickUpToken();
    //assuming Map is updated
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

  //At Red box, check if should drop off RED tokens
  if(mapGraph->getNumTokens(red) == 2){
    ///driveController->turn45(true, 4);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(red);
    driveController->turn45(true, 4);
    driveController->forwardToIntersection();
    driveController->turn45(false, 1);
  } else {
    //Can't drop off tokens
    //Turn robot to align with g1
    driveController->turn45(true,3);
  }

  //go to g1
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //Check if we can drop off GREEN tokens
  if(mapGraph->getNumTokens(green) == 2){
    //drop off green tokens on way by
    driveController->turn45(false, 2);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(green);
    driveController->turn45(true,4);
    driveController->forwardToIntersection();
  } else {
    driveController->turn45(true,2);
  }

  //go across to m1
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

  //Check if we can drop off MAGENTA tokens
  if(mapGraph->getNumTokens(magenta) == 2){
    //driveController->turnTo(2);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(magenta);
    driveController->turn45(true,4);
    driveController->forwardToIntersection();
    driveController->turn45(false,2);
  } else {
    driveController->turn45(true,2);
  }

  //go to c1
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //Check if depsoit CYAN tokens
  if( mapGraph->getNumTokens(cyan) == 2){
    //drop off cyan tokens on way by
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(cyan);
    driveController->turn45(true,4);
    driveController->forwardToIntersection();
  } {
    driveController->turn45(true,3);
  }

  //go to b1
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
  driveController->move(FWD);
  delay(1000);
  driveController->stop();
  tokenController->depositTokens(blue);

  //get back to b1
  driveController->turn45(true,4);
  driveController->forwardToIntersection();

  //go to g1
  driveController->turn45(true,1);
  driveController->forwardToIntersection();
  /*
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

}
 */
/*
void round2(){
	int inventory[6];
  time_t startTime = second();
  time_t endTime = 360 + startTime;
} */
/*
void round1(){
	int inventory[7];
  time_t startTime = second();
  time_t endTime = 300 + startTime; //5 minutes

  //start off at white box
  //go to the square that's closest to the gray box
  //go around said box and pick up tokens

  //once you hit y4 go to y2, traverse around the square
  //once you hit each's color's edge 2, check if we can despoit
  //after going once, if enough time deposit last tokens that nearest to you

  //Start at White Box closest to the yellow
  for (int i = 0; i < 5; i++) {
    driveController->forwardToIntersection();
  }

  driveController->turn45(false, 2);

  //---------------------------------------------------
  //          GO AROUND SQUARE 4 PHRASE

  ///Go to y4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //Go to m4
  driveController->turn45(true,2);
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //can we drop coins at MAGENTA
  if(mapGraph->getNumTokens(magenta) == 2){
    driveController->turn45(false,2);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(magenta);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,2);
  }

  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if can drop off CYAN tokens
  if(mapGraph->getNumTokens(cyan) == 2){
    driveController->turn45(false,1);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(cyan);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,1);
  } else {
    driveController->turn45(true,2);
  }

  //go to r4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off RED tokens
  if(mapGraph->getNumTokens(red) == 2){
    driveController->turn45(false,1);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(red);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,1);
  } else {
    driveController->turn45(true,2);
  }

  //go to g4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off GREEN tokens
  if (mapGraph->getNumTokens(green) == 2) {
    driveController->turn45(false,2);
    for (int i = 0; i < 4; i++) {
       driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(green);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,2);
  }

  //go to b4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off BLUE tokens
  if (mapGraph->getNumTokens(blue) == 2) {
    driveController->turn45(false,2);
    for (int i = 0; i < 4; i++) {
       driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(magenta);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,1);
  }  else {
    driveController->turn45(true,2);
  }

  ///go to y4
  driveController->forwardToIntersection();

  //---------------------------------------------------
  //          GO AROUND SQUARE 2 PHRASE

  //go to y2
  driveController->turn45(false,1);
  driveController->forwardToIntersection();
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off YELLOW tokens
  if (mapGraph->getNumTokens(yellow) == 2) {
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();

    driveController->move(FWD);
    delay(1000);
    driveController->stop();

    tokenController->depositTokens(yellow);
    driveController->turn45(false,4);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();
    driveController->turn45(false,1);
  } else {
    driveController->turn45(true,2);
  }


  //go to m2
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  if (mapGraph0>getNumTokens(magenta) >= 2) {
    driveController->turn45(false,2);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();

    driveController->move(FWD);
    delay(1000);
    driveController->stop();

    tokenController->depositTokens(magenta);
    driveController->turn45(false,4);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();
    driveController->turn45(false,2);
  }

  //go to cyan2
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  if (mapGraph0>getNumTokens(cyan) >= 2) {
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();

    driveController->move(FWD);
    delay(1000);
    driveController->stop();

    tokenController->depositTokens(magenta);
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();
    driveController->turn45(false,2);
  } else {
    driveController->turna45(true,2);
  }




}

/*
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
