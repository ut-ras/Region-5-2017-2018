#include "arrayline.h"
#include <Arduino.h>

arrayline::arrayline(){
	arrayLine = new SensorBar(I2C_ADDRESS);
  
	//Set it to strobe mode
	//IR only activates when read
	arrayLine->setBarStrobe();

	//Use this to continually have the IR active
	//arrayLine.clearBarStrobe();

	//White map with dark line:
	arrayLine->clearInvertBits();
 arrayLine->begin();
}

bool* arrayline::getLineSensor(){
	uint8_t rawValue = arrayLine->getRaw();
	//Print the binary value to the serial buffer.
	for( int i = 7; i >= 0; i--){
		boolArray[i] = (rawValue >> i) & 0x01;
    //Serial.print(boolArray[i]);Serial.print(" ");
	}
 //Serial.println();
}

bool arrayline::isLine(){
	
}
