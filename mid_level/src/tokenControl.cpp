#include "../inc/tokenControl.h"

//Distance from maxheight to ground
#define maxHeight 10.5
//Distance to fall into the funnel
#define funnelHeight 5.0
//Sets the direction of the magnet
#define up true
#define down false
//Delay to allow tokens to latch to magnet
#define pickupTime 1000;
//Delay pre and post drop off for stabalization
#define dropTime 250;
//Center to first funnel is 50 degrees
// 43.33333 between funnels
//Degrees from center to RGB Sesnor
#define toRGBSensor 20
//Degrees between each funnel
#define tokenToToken 43.33333333333333333333333333333333333333333333333333333333333333333333333333333333
//Degrees to first funnel from the RGB Sensor
#define toFirstToken 30
//Pin for the stepper motor
#define stepperPin 10

//Public

tokenControl::tokenControl() {
    //Initialize starter variables
    diskController(stepperPin);
    pulleyController();
    tokenReader();
    magnetController();
}

void tokenControl::pickUpToken() {
    //Drops magnet full distance, turns it on and waits for tokens, then returns it to base height
    lowerMagnet(maxHeight);
    magnetController.magnetOn();
    delay(pickupTime);
    raiseMagnet(maxHeight);
}

Node::Color tokenControl::storeToken() {
    //Reads token colour and if there is no token returns the electromagnet
    Node::Color colour = tokenReader.getColor();
    if(colour == Node::electromagnet)
        return colour;
    //Rotates the disk to the correct funnel, drops the tokens, then resets magnet
    rotateDisktoColor(colour);
    depositInFunnel();
    resetDisk(colour);
}

void tokenControl::depositTokens(Node::Color c) {
    //Moves to the correct funnel and picks up all the tokens
    rotateDiskToColor(c);
    pickupFromFunnel();
    //Moves token to center then deposits the tokens
    resetDisk(c);
    lowerMagnet(maxHeight);
    delay(dropTime);
    magnetController.magnetOff();
    delay(dropTime);
    //Reset the magnet
    raiseMagnet(maxHeight);
}

//Private

void tokenControl::lowerMagnet(double distance){
    pulleyController.movePulley(distance, up);
}

void tokenControl::raiseMagnet(double distance) {
    pulleyController.movePulley(distance, down);
}

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
    lowerMagnet(funnelHeight);
    delay(dropTime);
    magnetController.magnetOff();
    delay(dropTime);
    raiseMagnet(funnelHeight);
}

void tokenControll::pickupFromFunnel() {
    lowerMagnet(funnelHeight);
    magnetController.magnetOn();
    delay(pickupTime);
    raiseMagnet(funnelHeight);
}