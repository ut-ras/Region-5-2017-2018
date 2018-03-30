#include "tokenControl.h"
#include "Graph.h"
#include <Arduino.h>

//Servo Distances
//Distance from max height to ground - 10->5in
#define maxHeight 177
//Distance to fall into the funnel - 5in
#define funnelHeight 162
//Resting position
#define  resting 157
//Sets the direction of the magnet
#define up true
#define down false
//Pulley waits
#define funnelHeightWait 500
#define fullHeighWait 2000

//Magnet Times
//Delay to allow tokens to latch to magnet
#define pickupTime 1000
//Delay pre and post drop off for stbalization
#define dropTime 250


//Stepper Distances
//Center to first funnel is 50 degrees
// 43.33333 between funnels
//Degrees from center to RGB Sesnor
#define toRGBSensor 25
//Degrees between each funnel
#define tokenToToken 45
//Degrees to first funnel from the RGB Sensor
#define toFirstToken 20
//Pin for the stepper motor - needs proper assignment
#define stepPin 6
#define dirPin 7
//Pin for the magnet - needs proper assignment
#define magnetPin 11
//Pin for the servo - needs proper assignment
#define servoPin 12

//Public

tokenControl::tokenControl(Graph * m) {
	//colourSensor = new rgbsensor;
    diskController = new stepper(stepPin, dirPin);
    pulleyController = new r5servo();
    pulleyController->init(servoPin);
    magnetController = new magnet(magnetPin);
    mapGraph = m;
}

int tokenControl::pickUpToken() {
    //Drops magnet full distance, turns it on and waits for tokens, then returns it to base height
    moveToField(maxHeight);
    magnetController->magnetOn();
    delay(pickupTime);
    moveToField(resting);
    //Reads token colour and if there is no token returns the electromagnet
    int colour = Color::magenta;
    if(colour == Color::grey)
        return colour;

    //Rotates the disk to the correct funnel, drops the tokens, then resets magnet
    rotateDiskToColor(colour);
    resetDisk(colour);
    return colour;
}

void tokenControl::depositTokens(int c) {
    //Moves to the correct funnel and picks up all the tokens
    rotateDiskToColor(c);
    pickupFromFunnel();

    //Moves token to center then deposits the tokens
    resetDisk(c);
    moveToField(maxHeight);
    magnetController->magnetOff();
    delay(dropTime);

    //Reset the magnet
    moveToField(resting);
}

void tokenControl::goToEveryColour(){
  for(int i = 0; i < 7; i ++){
    rotateDiskToColor(i);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    resetDisk(i);
  }
}

void tokenControl::pickUpTokenTest(){
    moveToField(maxHeight);
    magnetController->magnetOn();
    delay(pickupTime);
    moveToField(maxHeight);
}

void tokenControl::pickupFromFunnelTest(int colour){
    rotateDiskToColor(colour);
    pickupFromFunnel();
    resetDisk(colour);
}

//Private

void tokenControl::rotateDiskToColor(int c) {
    //Finds most efficient direction for rotation
    if(c > 3){
        diskController->rotateDisk((7-c)*tokenToToken, stepper::COUNTERCLOCKWISE);
        delay(500 * (7-c));
    }else{
        diskController->rotateDisk((c+1)*tokenToToken, stepper::CLOCKWISE);
        delay(500*(c+1));
    }
}

void tokenControl::rotateDiskFromSensor(int c){
	if(c > 3){
		diskController->rotateDisk(toFirstToken, stepper::COUNTERCLOCKWISE);
		delay(500);
        diskController->rotateDisk((7-c)*tokenToToken, stepper::COUNTERCLOCKWISE);
        delay(500 * (7-c));
    }else{
        diskController->rotateDisk(toFirstToken, stepper::CLOCKWISE);
        delay(500);
        diskController->rotateDisk(c*tokenToToken, stepper::CLOCKWISE);
        delay(500*(c+1));
    }
}

int tokenControl::readColour(){
	int colour = 0;
	diskController->rotateDisk(toRGBSensor, stepper::CLOCKWISE);
	//colour = colourSensor->getColour();
	return colour;
}

void tokenControl::resetDisk(int c) {
    //Finds most efficient direction for rotation
    if(c > 3){
        diskController->rotateDisk((7-c)*tokenToToken, stepper::CLOCKWISE);
        delay(500 * (7-c));
    }else{
        diskController->rotateDisk((c+1)*tokenToToken, stepper::COUNTERCLOCKWISE);
        delay(500*(c+1));
    }
}

void tokenControl::depositInFunnel() {
    pulleyController->movePulley(funnelHeight);
    delay(dropTime);
    magnetController->magnetOff();
    delay(dropTime);
    pulleyController->movePulley(resting);
}

void tokenControl::pickupFromFunnel() {
    pulleyController->movePulley(funnelHeight);
    delay(funnelHeightWait);
    magnetController->magnetOn();
    delay(pickupTime);
    pulleyController->movePulley(resting);
    delay(funnelHeightWait);
}

void tokenControl::moveToField(int angle){
    pulleyController->movePulley(angle);
    delay(fullHeighWait);
}