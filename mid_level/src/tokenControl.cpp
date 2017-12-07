#include "../inc/tokenControl.h"

#define maxHeight 10.5
#define funnelHeight 5.0
#define up true
#define down false
#define pickupTime 1000;
#define dropTime 250;
//Center to first funnel is 50 degrees
// 43.33333 between funnels
#define toRGBSensor 20
#define tokenToToken 43.33333333333333333333333333333333333333333333333333333333333333333333333333333333
#define toFirstToken 30
#define stepperPin 10

//Public

tokenControl::tokenControl() {
    diskController = *(new stepper(stepperPin));
    pulleyController = *(new servo());
    tokenReader = *(new rgbsensor());
    magnetController = *(new magnet());
}

void tokenControl::pickUpToken() {
    lowerMagnet(maxHeight);
    magnetController.magnetOn();
    delay(pickupTime);
    raiseMagnet(maxHeight);
}

Node::Color tokenControl::storeToken() {
    Node::Color colour = tokenReader.getColor();
    if(colour == Node::electromagnet)
        return colour;
    rotateDisktoColor(colour);
    depositInFunnel();
    resetDisk(colour);
    delete(colour);
}

void tokenControl::depositTokens(Node::Color c) {
    rotateDiskToColor(c);
    pickupFromFunnel();
    resetDisk(c);
    lowerMagnet(maxHeight);
    delay(dropTime);
    magnetController.magnetOff();
    delay(dropTime);
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
    if(c > 3){
        diskController.rotateDisk(toFirstToken + toRGBSensor, stepper::COUNTERCLOCKWISE);
        diskController.rotateDisk((7-c)*tokenToToken, stepper::COUNTERCLOCKWISE);
    }else{
        diskController.rotateDisk(toFirstToken, stepper::CLOCKWISE);
        diskController.rotateDisk(c*tokenToToken, stepper::CLOCKWISE);
    }
}

void tokenControl::resetDisk(Node::Color c) {
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