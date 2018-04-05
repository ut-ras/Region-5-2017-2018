#include "arrayline.h"
#include <Arduino.h>

arrayline::arrayline(int stype){
	sensorType = stype;

	if (sensorType == LS_ANALOG) {
		//QTRSensorsAnalog(unsigned char* analogPins, unsigned char numSensors, unsigned char numSamplesPerSensor = 4, unsigned char emitterPin = QTR_NO_EMITTER_PIN)
		unsigned char pins[8] = {ARRAYP0, ARRAYP1, ARRAYP2, ARRAYP3, ARRAYP4, ARRAYP5, ARRAYP6, ARRAYP7};
		arrayLineA = new QTRSensorsAnalog(&pins[0], 8);

		//set up calibration data from saved tested values
		//setCalibration();
    //or, run calibration
    calibrateSensors();
	}
	else {
		arrayLineD = new SensorBar(I2C_ADDRESS);
	  
		//Set it to strobe mode
		//IR only activates when read
		arrayLineD->setBarStrobe();

		//White map with dark line:
		arrayLineD->clearInvertBits();
	 	arrayLineD->begin();
	 }
}



int arrayline::getLinePosition() {
	//assuming that 0 is to the left here, so switch if 0 is near the right
	if (sensorType == LS_ANALOG) {
		unsigned int sensors[8];
	  int position = arrayLineA->readLine(sensors);		//this is between 0 and 7000 so subtract 4000
		position -= 3500;
		return position; 
	}
	else { 
		uint8_t rawValue = arrayLineD->getRaw();
		rawValue = ~rawValue;
		double sum = 0;
		double notZero = 0;
		for(int i = 0; i<8; i++) {
		  	//sum += weights[i]*((rawValue>>i)&0x01);
			sum += i*1000*((rawValue>>i)&0x01);
		  	if (((rawValue>>i) & 0x01) != 0) { notZero++; }
		}
		sum -= 4000;
		return (notZero == 0)?0:(sum / notZero);
	}
}

int arrayline::getWeightedValue(){
  int pos = getLinePosition();
  return pos *= weights[(pos + 4000) / 1000];
}



//calibration stuff for the analog sensor (library's readLine function uses this calibration to create a weight)

//return and print calibration data, add output to arrays in h file
//run this once, record data, store in H file, and then call setCalibration in constructor
int* arrayline::calibrateSensors() {
  Serial.println("Starting Front Line Calibration (about 5s)");
  delay(1000);
  int i;
  	for (i = 0; i < 350; i++)  { // make the calibration take about 5 seconds	  
    arrayLineA->calibrate();
    delay(20);
  }
  
  //this wont save in between runs, so print results and add to h file before competiton 
  printAnalogCalibration();
  while(1);
	
}

void arrayline::setCalibration() {
	printAnalogCalibration();
	arrayLineA->calibratedMinimumOn = calibratedMinimumOn;
	arrayLineA->calibratedMaximumOn = calibratedMaximumOn;
}

void arrayline::printAnalogCalibration() {
	Serial.print("calibratedMinimumOn: ");
	for (int i = 0; i < 8; i++) {
		Serial.print(String(calibratedMinimumOn[i]) + " ");
	}
	Serial.println();

	Serial.print("calibratedMaximumOn: ");
	for (int i = 0; i < 8; i++) {
		Serial.print(String(calibratedMaximumOn[i]) + " ");
	}
	Serial.println();

  /* we're leaving the emitter on so these don't really matter
	Serial.print("calibratedMinimumOff: ");
	for (int i = 0; i < 8; i++) {
		Serial.print(String(calibratedMinimumOff[i]) + " ");
	}
	Serial.println();

	Serial.print("calibratedMaximumOff: ");
	for (int i = 0; i < 8; i++) {
		Serial.print(String(calibratedMaximumOff[i]) + " ");
	}
	Serial.println();
 */
}
