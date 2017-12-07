#include "../inc/arrayline.h"

<<<<<<< HEAD
arrayline::arrayline(){
	arrayLine = new SensorBar(I2C_ADDRESS);

	//Set it to strobe mode
	//IR only activates when read
	arrayLine.setBarStrobe();

	//Use this to continually have the IR active
	//arrayLine.clearBarStrobe();

	//White map with dark line:
	arrayLine.clearInvertBits();
}

bool[LINESENSOR_SIZE] arrayline::getLineSensor(){
	uint8_t rawValue = arrayLine.getRaw();

	//Print the binary value to the serial buffer.
	for( int i = 7; i >= 0; i--){
		boolArray[i] = (rawValue >> i) & 0x01;
	}
}

bool arrayline::isLine(){
	
=======
arrayline::arrayline(uint8_t _I2C_ADDRESS){

>>>>>>> 3a612d926e51497f15cc639e5b2b9520b6da8f29
}
