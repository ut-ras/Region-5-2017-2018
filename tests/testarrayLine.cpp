SensorBar arrayLine;

void setuparrayLineTest(){
	serial.begin(9600);

	arrayLine = new SensorBar(I2C_ADDRESS); 
}

void looparrayLineTest(){
	Serial.println(arrayLine.isLine());
}