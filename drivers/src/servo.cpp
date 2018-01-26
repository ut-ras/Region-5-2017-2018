#include "../inc/servo.h"
#include <Servo.h>

//servo inputs go from 10 - 180 , running below 10 results in constant slow rotation
servo::servo(int _servoPin){
	servoPos = 180;
	thisServo.attach(_servoPin);
	thisServo.write(servoPos);	//initialize the servo to the start servo position
	delay(100);
}

void servo::movePulley(double distance, bool direction){
	if(direction)
		servoPos -= (distance / 4) * 170;
	else
		servoPos += (distance / 4) * 170;
	thisServo.write(servoPos);
	delay(100);
}