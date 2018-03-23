#include "MotorControl.h"
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

MotorControl::MotorControl() {
  //Field Initializations

  leftEncoder = new encoder(2,4);
  rightEncoder = new encoder(3,5);

  AFMS = new Adafruit_MotorShield();

  myMotor = AFMS->getMotor(1);
  myOtherMotor = AFMS->getMotor(2);

  prevTime = 0;

  leftPrevEncoderPos = 0;

  leftKp = 2;
  leftKi = 5;
  leftKd = 1;
  leftMotorPID = new PID(&leftVelocity, &leftPower, &leftSetpoint,leftKp,leftKi,leftKd, DIRECT);

  rightPrevEncoderPos = 0;

  rightKp = 2;
  rightKi = 5;
  rightKd = 1;
  rightMotorPID = new PID(&rightVelocity, &rightPower, &rightSetpoint,rightKp,rightKi,rightKd, DIRECT);

  //Motor Initialization
  AFMS->begin();  // create with the default frequency 1.6KHz

  myMotor->run(FORWARD);
  myOtherMotor->run(FORWARD);
  myMotor->setSpeed(120);
  myOtherMotor->setSpeed(120);

  //PID Initialization
  leftMotorPID->SetSampleTime(10);
  leftMotorPID->SetMode(AUTOMATIC);
  leftMotorPID->SetOutputLimits(-255,255);

  rightMotorPID->SetSampleTime(10);
  rightMotorPID->SetMode(AUTOMATIC);
  rightMotorPID->SetOutputLimits(-255,255);

  //delay for testing purposes
  delay(5000);
  Serial.print("DELAYDONE");
}

void MotorControl::setMotorAction(char a){
  motorAction = a;
}

void MotorControl::setMotorSpeed(char s){
  if(s == '1'){
    motorSpeed = 90;
  }
  if(s == '2'){
    motorSpeed = 135;
  }
  if(s == '3'){
    motorSpeed = 180;
  }
}

void MotorControl::setMotorDirection(char d){
  if(d == 'f'){
    motorDirection = 1;
  }
  if(d = 'b'){
    motorDirection = -1;
  }
}


void MotorControl::update(){
  int16_t leftPosition,rightPosition;

  leftPosition = leftEncoder->getPos();
  rightPosition = rightEncoder->getPos();

  /* For Testing Purposes
  Serial.print(leftPosition);
  Serial.print(", ");
  Serial.print(rightPosition);
  Serial.print("\n");
  */

  calculateVelocity();

  switch(motorAction){
    case 'm':
      setPIDSpeed(motorSpeed*motorDirection,motorSpeed*motorDirection);
      break;
    case 't':
      setPIDSpeed(motorSpeed*motorDirection,motorSpeed*motorDirection*-1);
      break;
    case 's':
      setPIDSpeed(0,0);
      break;
  }
}

void MotorControl::setPIDSpeed(int leftSpeed, int rightSpeed) {
  leftSetpoint = leftSpeed;
  leftMotorPID->Compute();
  if(leftPower < 0 ){
    myMotor->run(BACKWARD);
  }else{
    myMotor->run(FORWARD);
  }
  myMotor->setSpeed(abs((int)leftPower));

  rightSetpoint = rightSpeed;
  rightMotorPID->Compute();
    if(rightPower < 0 ){
    myOtherMotor->run(BACKWARD);
  }else{
    myOtherMotor->run(FORWARD);
  }
  myOtherMotor->setSpeed(abs((int)rightPower));
}

void MotorControl::calculateVelocity() {
  time = 0.001*millis();
  leftVelocity = 2*(leftEncoder->getPos() - leftPrevEncoderPos)/(time-prevTime); //need to linearize
  leftPrevEncoderPos = leftEncoder->getPos();
  rightVelocity = 2*(rightEncoder->getPos() - rightPrevEncoderPos)/(time-prevTime); //need to linearize
  rightPrevEncoderPos = rightEncoder->getPos();
  prevTime = time;
}

void MotorControl::setMotorMode(int c) {
  switch(c){
    case m1f:
      setMotorAction('m');
      setMotorSpeed('1');
      setMotorDirection('f');
      break;
    case m2f:
      setMotorAction('m');
      setMotorSpeed('2');
      setMotorDirection('f');
      break;
    case m3f:
      setMotorAction('m');
      setMotorSpeed('3');
      setMotorDirection('f');
      break;
    case m1b:
      setMotorAction('m');
      setMotorSpeed('1');
      setMotorDirection('b');
      break;
    case m2b:
      setMotorAction('m');
      setMotorSpeed('2');
      setMotorDirection('b');
      break;
    case m3b:
      setMotorAction('m');
      setMotorSpeed('3');
      setMotorDirection('b');
      break;
    case t1f:
      setMotorAction('t');
      setMotorSpeed('1');
      setMotorDirection('f');
      break;
    case t1b:
      setMotorAction('t');
      setMotorSpeed('1');
      setMotorDirection('b');
      break;
    case s:
      setMotorAction(s);
      break;
  }
}
