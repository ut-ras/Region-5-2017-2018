	#include "tokenControl.h"

//Servo Distances
//Distance from max height to ground - 10.5in
#define maxHeight 160
//Distance to fall into the funnel - 5in
#define funnelHeight 175
//Resting position
#define  resting 180
//Sets the direction of the magnet
#define up true
#define down false

//Magnet Times
//Delay to allow tokens to latch to magnet
#define pickupTime 1000;
//Delay pre and post drop off for stbalization
#define dropTime 250;


//Stepper Distances
//Center to first funnel is 50 degrees
// 43.33333 between funnels
//Degrees from center to RGB Sesnor
#define toRGBSensor 20
//Degrees between each funnel
#define tokenToToken 43.33333333333333333333333333333333333333333333333333333333333333333333333333333333
//Degrees to first funnel from the RGB Sensor
#define toFirstToken 30
//Pin for the stepper motor - needs proper assignment
#define stepperPin 10
//Pin for the magnet - needs proper assignment
#define magnetPin 11
//Pin for the servo - needs proper assignment
#define servoPin 12

//Public

tokenControl::tokenControl() {
    //Initialize starter variables
    diskController(stepperPin);
    pulleyController(servoPin);
    tokenReader();
    magnetController(magnetPin);
}

Node::Color tokenControl::pickUpToken() {
    //Drops magnet full distance, turns it on and waits for tokens, then returns it to base height
    pulleyController.movePulley(maxheight);
    magnetController.magnetOn();
    delay(pickupTime);
    pulleyController.movePulley(resting);

    //Reads token colour and if there is no token returns the electromagnet
    Node::Color colour = tokenReader.getColor();
    if(colour == Node::electromagnet)
        return colour;

    //Rotates the disk to the correct funnel, drops the tokens, then resets magnet
    rotateDisktoColor(colour);
    depositInFunnel();
    resetDisk(colour);
    return colour;
}

void tokenControl::depositTokens(Node::Color c) {
    //Moves to the correct funnel and picks up all the tokens
    rotateDiskToColor(c);
    pickupFromFunnel();

    //Moves token to center then deposits the tokens
    resetDisk(c);
    pulleyController.movePulley(maxHeight);
    delay(dropTime);
    magnetController.magnetOff();
    delay(dropTime);

    //Reset the magnet
    pulleyController.movePulley(resting);
}

//Private

void tokenControl::rotateDiskToColor(Node::Color c) {
    //Finds most efficient direction for rotation
    if(c > 3){
        diskController.rotateDisk(toFirstToken + toRGBSensor, stepper::COUNTERCLOCKWISE);
        diskController.rotateDisk((7-c)*tokenToToken, stepper::COUNTERCLOCKWISE);
    }else{
        diskController.rotateDisk(toFirstToken, stepper::CLOCKWISE);
        diskController.rotateDisk(c*tokenToToken, stepper::CLOCKWISE);
    }
}

void tokenControl::resetDisk(Node::Color c) {
    //Finds most efficient direction for rotation
    if(c > 3){
        diskController.rotateDisk(toFirstToken + toRGBSensor, stepper::CLOCKWISE);
        diskController.rotateDisk((7-c)*tokenToToken, stepper::CLOCKWISE);
    }else{
        diskController.rotateDisk(toFirstToken, stepper::COUNTERCLOCKWISE);
        diskController.rotateDisk(c*tokenToToken, stepper::COUNTERCLOCKWISE);
    }
}

void tokenControl::depositInFunnel() {
    pulleyController.movePulley(funnelHeight);
    delay(dropTime);
    magnetController.magnetOff();
    delay(dropTime);
    pulleyController.movePulley(resting);
}

void tokenControll::pickupFromFunnel() {
	pulleyController.movePulley(funnelHeight);
    magnetController.magnetOn();
    delay(pickupTime);
    pulleyController.movePulley(resting);
}