#include "stepper.h"

//servo inputs go from 10 - 180 , running below 10 results in constant slow rotation
stepper::stepper(int _stepperPin){
	servoPos = 180;
	thisServo.attach(_stepperPin);
	thisServo.write();	//initialize the servo to the start servo position
	delay(100);
}

void rotateDisk(uint8_t holeOffset, Direction rotationDirection){
	
}
