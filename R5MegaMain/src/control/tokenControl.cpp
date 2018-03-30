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

//Magnet Times
//Delay to allow tokens to latch to magnet
#define pickupTime 1000
//Delay pre and post drop off for stbalization
#define dropTime 250


//Stepper Distances
//Center to first funnel is 50 degrees
// 43.33333 between funnels
//Degrees from center to RGB Sesnor
#define toRGBSensor 20
//Degrees between each funnel
#define tokenToToken 43.33333333333333333333333333333333333333333333333333333333333333333333333333333333
//Degrees to first funnel from the RGB Sensor
#define toFirstToken 35
//Pin for the stepper motor - needs proper assignment
#define stepPin 6
#define dirPin 7
//Pin for the magnet - needs proper assignment
#define magnetPin 11
//Pin for the servo - needs proper assignment
#define servoPin 12

//Public

tokenControl::tokenControl(Graph * m) {
  diskController = new stepper(stepPin, dirPin);
  pulleyController = new r5servo();
  pulleyController->init(servoPin);
  magnetController = new magnet(magnetPin);
  mapGraph = m;
}

int tokenControl::pickUpToken() {
    //Drops magnet full distance, turns it on and waits for tokens, then returns it to base height
    pulleyController->movePulley(maxHeight);
    magnetController->magnetOn();
    delay(2000);
    delay(pickupTime);
    pulleyController->movePulley(resting);
    delay(2000);
    //Reads token colour and if there is no token returns the electromagnet
    int colour = Color::green;
    if(colour == Color::grey)
        return colour;

    //Rotates the disk to the correct funnel, drops the tokens, then resets magnet
    diskController->rotateDisk(360,0);
    delay(3000);
    diskController->rotateDisk(360,1);
    rotateDiskToColor(colour);
    depositInFunnel();
    delay(3000);
    resetDisk(colour);
    return colour;
}

void tokenControl::depositTokens(int c) {
    //Moves to the correct funnel and picks up all the tokens
    rotateDiskToColor(c);
    pickupFromFunnel();

    //Moves token to center then deposits the tokens
    resetDisk(c);
    pulleyController->movePulley(maxHeight);
    delay(dropTime);
    magnetController->magnetOff();
    delay(dropTime);

    //Reset the magnet
    pulleyController->movePulley(resting);
}

//Private

void tokenControl::rotateDiskToColor(int c) {
    //Finds most efficient direction for rotation
    if(c > 3){
        diskController->rotateDisk(toFirstToken + toRGBSensor, stepper::COUNTERCLOCKWISE);
        delay(2000);
        diskController->rotateDisk((7-c)*tokenToToken, stepper::COUNTERCLOCKWISE);
    }else{
        diskController->rotateDisk(toFirstToken, stepper::CLOCKWISE);
        diskController->rotateDisk(c*tokenToToken, stepper::CLOCKWISE);
    }
}

void tokenControl::resetDisk(int c) {
    //Finds most efficient direction for rotation
    if(c > 3){
        diskController->rotateDisk(toFirstToken + toRGBSensor, stepper::CLOCKWISE);
        diskController->rotateDisk((7-c)*tokenToToken, stepper::CLOCKWISE);
    }else{
        diskController->rotateDisk(toFirstToken, stepper::COUNTERCLOCKWISE);
        diskController->rotateDisk(c*tokenToToken, stepper::COUNTERCLOCKWISE);
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
    magnetController->magnetOn();
    delay(pickupTime);
    pulleyController->movePulley(resting);
}
