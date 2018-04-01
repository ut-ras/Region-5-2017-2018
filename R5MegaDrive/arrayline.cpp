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
    Serial.print(boolArray[i]);Serial.print(" ");
	}
 Serial.println();
}

int arrayline::getWeightedValue() {
  uint8_t rawValue = arrayLine->getRaw();
  rawValue = ~rawValue;
  double sum = 0;
  double notZero = 0;
  for(int i = 0; i<8; i++) {
    sum += weights[i]*((rawValue>>i)&0x01);
    if (((rawValue>>i) & 0x01) != 0) { notZero++; }
  }
  //Serial.println("notzero " + String(notZero));
  //Serial.println(sum / notZero);
  return (notZero == 0)?0:(sum / notZero);
}


bool arrayline::isLine(){
	
}
