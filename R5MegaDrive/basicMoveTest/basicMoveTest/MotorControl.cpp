#include "MotorControl.h"
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

MotorControl::MotorControl(int lA, int lB, int rA, int rB) {
  //Field Initializations

  leftEncoder = new encoder(lA,lB);
  rightEncoder = new encoder(rA,rB);

  Serial.println("inside init");
  
  AFMS = new Adafruit_MotorShield();

  myMotor = AFMS->getMotor(3);
  myOtherMotor = AFMS->getMotor(1);

  Serial.println("AFMS init");
  
  prevTime = 0;

  leftPrevEncoderPos = 0;

  leftKp = 0.2;
  leftKi = 0.5;
  leftKd = 0.1;
  leftMotorPID = new PID(&leftVelocity, &leftPower, &leftSetpoint,leftKp,leftKi,leftKd, DIRECT);

  rightPrevEncoderPos = 0;

  rightKp = 0.2;
  rightKi = 0.5;
  rightKd = 0.1;
  rightMotorPID = new PID(&rightVelocity, &rightPower, &rightSetpoint,rightKp,rightKi,rightKd, DIRECT);

  Serial.println("PID init");
  
  //Motor Initialization
  AFMS->begin();  // create with the default frequency 1.6KHz

  //myMotor->run(FORWARD);
  //myOtherMotor->run(FORWARD);
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
  delay(1000);
  Serial.println("Motor Control Initialized");
}

encoder* MotorControl::getLeftEncoder() {
  return leftEncoder;
}

encoder* MotorControl::getRightEncoder() {
  return rightEncoder;
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
  
  Serial.print("Power:" + String(leftVelocity) +  " / " + String(rightVelocity));
  Serial.print(" Velocity:" + String(leftPower) +  " / " + String(rightPower) + "\n");

  switch(motorAction){
    case 'm':
      setPIDSpeed(motorSpeed*motorDirection, motorSpeed*motorDirection);
      break;
    case 't':
      setPIDSpeed(motorSpeed*motorDirection, motorSpeed*motorDirection*-1);
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
  //Serial.println("Set Motor Speeds");
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
    case FWD1:
      setMotorAction('m');
      setMotorSpeed('1');
      setMotorDirection('f');
      break;
    case FWD2:
      setMotorAction('m');
      setMotorSpeed('2');
      setMotorDirection('f');
      break;
    case FWD3:
      setMotorAction('m');
      setMotorSpeed('3');
      setMotorDirection('f');
      break;
    case BACK1:
      setMotorAction('m');
      setMotorSpeed('1');
      setMotorDirection('b');
      break;
    case BACK2:
      setMotorAction('m');
      setMotorSpeed('2');
      setMotorDirection('b');
      break;
    case BACK3:
      setMotorAction('m');
      setMotorSpeed('3');
      setMotorDirection('b');
      break;
    case LEFT:
      setMotorAction('t');
      setMotorSpeed('1');
      setMotorDirection('f');
      break;
    case RIGHT:
      setMotorAction('t');
      setMotorSpeed('1');
      setMotorDirection('b');
      break;
    case STOP:
      setMotorAction('s');
      break;
  }
}