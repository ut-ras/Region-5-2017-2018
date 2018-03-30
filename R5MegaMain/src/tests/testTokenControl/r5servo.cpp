#include "r5servo.h"
#include <Servo.h>
#include <Arduino.h>

//constructor
r5servo::r5servo(){}

//servo inputs go from 10 - 180 , running below 10 results in constant slow rotation
void r5servo::init(int _servoPin){
  servoPos = 157;
  thisServo.attach(_servoPin);
  thisServo.write(servoPos);  //initialize the servo to the start servo position
  delay(100);
}

void r5servo::movePulley(int degrees){
  servoPos = degrees;
  thisServo.write(servoPos);
  delay(100);
}
