
servo s;

void setupServoTest(){
	s = new servo();
	Serial.begin(9600);
	Serial.println("Servo Test...");
}

void loopServoTest(){
	servo.movePulley(1, true);
	Serial.println("Moved down 1 unit...");
	servo.movePulley(1, false);
	Serial.println("Moved back up 1 unit...");
}