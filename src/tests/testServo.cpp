
servo s;

void setupServoTest(){
	s = new servo();
	Serial.begin(9600);
	Serial.println("Servo Test...");
}

void loopServoTest(){
	servo.movePulley(180);
	Serial.println("Moved to position 180");
	servo.movePulley(160);
	Serial.println("Moved to position 160");
}