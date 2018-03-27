#include "r5servo.h"
#include <Servo.h>
#include <Arduino.h>

//servo inputs go from 10 - 180 , running below 10 results in constant slow rotation
r5servo::r5servo(int _servoPin){
	servoPos = 180;
	thisServo.attach(_servoPin);
	thisServo.write(servoPos);	//initialize the servo to the start servo position
	delay(100);
}

void r5servo::movePulley(double degrees){
	servoPos = degrees;
	thisServo.write(servoPos);
	delay(100);
}
