#include "../inc/motorController.h"

motorController::motorController(int _boardAddress, int _shieldAddress){

	Wire.onReceive(receiveEvent);
	Wire.begin(0x10);
	//Attach the board to the shield
	Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

	//Attach the motors
	Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
	Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);

	//Default frequency: 1.6 KHz
	AFMS.begin();
	//AFMS.begin(1000); //1000Hz for example

	//Initialize motors:
	rightMotor->setSpeed(0);
	leftMotor->setSpeed(0);
	rightMotor->run(FORWARD);
	leftMotor->run(FORWARD);
	rightMotor->run(RELEASE);
	leftMotor->run(RELEASE);
}

void motorController::moveForward(double distance){
	rightMotor->run(FORWARD);
	leftMotor->run(FORWARD);
	rightMotor->setSpeed(255);
	rightMotor->setSpeed(255);
	//Have to get the encoders working
}

void motorController::moveBackward(double distance){
	rightMotor->run(BACKWARD);
	leftMotor->run(BACKWARD);
	rightMotor->setSpeed(255);
	rightMotor->setSpeed(255);
	//Have to make a encoder data receiver I think
}

void motorController::turn(double angleDegrees){
	if(angleDegrees > 0){
		rightMotor->run(BACKWARD);
		leftMotor->run(FORWARD);
		rightMotor->setSpeed(127);
		leftMotor->setSpeed(127);
		//Make something for the gyro to tell how much of an arc we have to cover
	} else if(angleDegrees < 0){
		rightMotor->run(FORWARD);
		leftMotor->run(BACKWARD);
		rightMotor->setSpeed(127);
		leftMotor->setSpeed(127);
	} else if(angleDegrees == 0){
		moveForward(distance);
	}
}

//Not part of the motorController class
//What happens when the Mega asks for it to move?
void receiveEvent(int numBytes){

}
