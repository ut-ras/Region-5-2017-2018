#ifndef arrayline_h
#define arrayline_h

#include "Wire.h"
#include "sensorbar.h"

#define LINESENSOR_SIZE 8
#define I2C_ADDRESS 0x3E

class arrayline {
private:
	SensorBar* arrayLine;
	bool boolArray [LINESENSOR_SIZE];

	uint8_t rawValue;
  int8_t weights[8] = {-8, -4, -2, -1, 1, 2, 4, 8};

public:

	//Since we only have 1 line sensor we can just
	//use the macro number I2C_ADDRESS
	arrayline();

    //Get line sensor array for line sensor values
    bool* getLineSensor();

    //Check if any of the 8 sensors are true
    bool isLine();

    int getWeightedValue();

};

#endif
