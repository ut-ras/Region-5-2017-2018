#ifndef arrayline_h
#def arrayline_h

#include "Arduino.h"
#include "Wire.h"
#include "sensorbar."

#define LINESENSOR_SIZE 8
#define I2C_ADDRESS 0x3E

class arrayline {
private:
	SensorBar arrayLine;
	bool[LINESENSOR_SIZE] boolArray;

	uint8_t rawValue;
public:

	//Since we only have 1 line sensor we can just
	//use the macro number I2C_ADDRESS
	arrayline();

    //Get line sensor array for line sensor values
    bool[LINESENSOR_SIZE] getLineSensor();

    //Check if any of the 8 sensors are true
    bool isLine();

};

#endif
