#include "../inc/motorController.h"

oneRotation = 3.1 * 2 * 3.14159265358979323846;


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
	//Have to get the encoders working
}

void motorController::turn(double angleDegrees){
	//Have to get the encoders working
}

//Not part of the motorController class
//What happens when the Mega asks for it to move?
void receiveEvent(int numBytes){
	
}