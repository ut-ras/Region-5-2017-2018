#ifndef motorController_h
#def motorController_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class MotorController {
public:
	//Initializes the motor shield and i2c communication between
	//the Mega and the UNO controlling the shield
	MotorController(int boardAddress, int shieldAddress);
	
	//Attaches a motor at the specified port (M1 = 1, M2 = 2...)
	void attachMotor(int motor);

    //Moves forward a certain distance
    void moveForward(double distance);

    //Move backward a certain distance
    void moveBackward(double distance);

    //Turn at an angle
    void turn(double angleRadians);

};

#endif