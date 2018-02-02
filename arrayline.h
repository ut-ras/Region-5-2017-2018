#ifndef arrayline_h
#define arrayline_h

#include "Wire.h"
#include "sensorbar.h"

#define LINESENSOR_SIZE 8
#define I2C_ADDRESS 0x3E

class arrayline {
private:
	SensorBar arrayLine;
	bool boolArray [LINESENSOR_SIZE];

	uint8_t rawValue;
public:

	//Since we only have 1 line sensor we can just
	//use the macro number I2C_ADDRESS
	arrayline();

    //Get line sensor array for line sensor values
    bool* getLineSensor();

    //Check if any of the 8 sensors are true
    bool isLine();

};

#endif
