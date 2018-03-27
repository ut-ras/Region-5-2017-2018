#include "MotorControl.h"
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

MotorControl::MotorControl(int lA, int lB, int rA, int rB) {
  //Field Initializations

  leftEncoder = new encoder(lA,lB);
  rightEncoder = new encoder(rA,rB);

  AFMS = new Adafruit_MotorShield();

  leftMotor = AFMS->getMotor(1);
  rightMotor = AFMS->getMotor(2);

  lineSensor = new arrayline();

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

  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
  leftMotor->setSpeed(120);
  rightMotor->setSpeed(120);

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

void MotorControl::calculateCorrections(int* correctionLeft, int* correctionRight){
  int lineSensorWeight = lineSensor->getWeightedValue();
  if(lineSensorWeight < -8){
    *correctionLeft = 4;   
  }else if((lineSensorWeight >= -8)&&(lineSensorWeight < -2)){
    *correctionLeft = 2;
  }else if((lineSensorWeight >= 2)&&(lineSensorWeight < 8)){
    *correctionRight = 2;   
  }else if(lineSensorWeight > 8){
    *correctionRight = 4;   
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

  int correctionL, correctionR;
  switch(motorAction){
    case 'm':
      correctionL = 0;
      correctionR = 0;
      calculateCorrections(&correctionL, &correctionR);
      setPIDSpeed(motorSpeed*motorDirection + correctionL, motorSpeed*motorDirection + correctionR);
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
    leftMotor->run(BACKWARD);
  }else{
    leftMotor->run(FORWARD);
  }
  leftMotor->setSpeed(abs((int)leftPower));

  rightSetpoint = rightSpeed;
  rightMotorPID->Compute();
  if(rightPower < 0 ){
    rightMotor->run(BACKWARD);
  }else{
    rightMotor->run(FORWARD);
  }
  rightMotor->setSpeed(abs((int)rightPower));
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
