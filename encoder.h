#ifndef encoder_h
#def encoder_h

#include "Arduino.h"
#include <Wire.h>
#include <digitalWriteFast.h>

class encoder{
public:
	//Initializes the encoder and i2c communication between
	//the Nano and Mega
	encoder(int _masterAddress, int _slaveAddress);
	
	//Return the current encoder value
	long getCurrentDistance();
	
	//Resets the encoder value to 0
	void resetEncoder();
	
	//Interrupt drivers
	void HandleLeftMotorInterruptA();
	void HandleLeftMotorInterruptB();
	
	//Increments or decrements current encoder value
	int ParseEncoder();
	
	//I2C request event
	//Sends data over to the Mega when requested
	void requestEvent();
	
private:
	volatile bool _LeftEncoderASet;
	volatile bool _LeftEncoderBSet;
	volatile bool _LeftEncoderAPrev;
	volatile bool _LeftEncoderBPrev;
	volatile long _LeftEncoderTicks;
}

#endif