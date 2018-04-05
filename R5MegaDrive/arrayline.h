#ifndef arrayline_h
#define arrayline_h

#include "Wire.h"
#include "sensorbar.h"
#include <QTRSensors.h>

#define LINESENSOR_SIZE 8
#define I2C_ADDRESS 0x3E

//for analog array
#define ARRAYP0 A8
#define ARRAYP1 A9
#define ARRAYP2 A10
#define ARRAYP3 A11
#define ARRAYP4 A12
#define ARRAYP5 A13
#define ARRAYP6 A14
#define ARRAYP7 A15

//library for analog line sensor: QTRSensors

enum LineArrayTypes {LS_DIGITAL, LS_ANALOG};

class arrayline {
private:
	SensorBar* arrayLineD;				//sparkfun digital
	QTRSensorsAnalog* arrayLineA;		//pololu analog

	bool boolArray [LINESENSOR_SIZE];

	uint8_t rawValue;
	int8_t weights[8] = {-8, -4, -2, -1, 1, 2, 4, 8};

	int sensorType = 0; //ANALOG or DIGITAL

	//for analog, calibration stuff
	unsigned int calibratedMinimumOn[8] = {37, 36, 35, 33, 32, 34, 34, 36};
	unsigned int calibratedMaximumOn[8] = {889, 834, 766, 791, 770, 781, 804, 802};


public:

	//Since we only have 1 line sensor we can just
	//use the macro number I2C_ADDRESS
	arrayline(int stype);

	//Get line sensor array for line sensor values
	int getLinePosition();
	int getWeightedValue();

 //for analog calibration
 int* calibrateSensors();
 void printAnalogCalibration();
 void setCalibration();

};

#endif
