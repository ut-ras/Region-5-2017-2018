#ifndef arrayline_h
#def arrayline_h

#include "Arduino.h"
#include "Wire.h"
#include "sensorbar."

#define LINESENSOR_SIZE 8
#define I2C_ADDRESS 0x3E

class arrayline {
private:
	

public:

	arrayline(uint8_t _I2C_ADDRESS);
	
    //Get line sensor array for line sensor values
    bool[LINESENSOR_SIZE] getLineSensor();

    //Check if any of the 8 sensors are true
    bool isLine();

};

#endif