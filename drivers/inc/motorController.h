#ifndef motorController_h
#def motorController_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class motorController {
public:
	//Initializes the motor shield and i2c communication between
	//the Mega and the UNO controlling the shield
	motorController(int _boardAddress, int _shieldAddress);

    //Moves forward a certain distance
    void moveForward(float distance);

    //Move backward a certain distance
    void moveBackward(float distance);

    //Turn at an angle
    void turn(float angleDegrees);
	
	//I2C receive event
	void receiveEvent(int numbytes);
	
private:
	Adafruit_MotorShield AFMS;

	Adafruit_DCMotor *rightMotor;
	Adafruit_DCMotor *leftMotor;
	
	float oneRotation;

};

#endif