#include "MotorControl.h"
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

MotorControl::MotorControl(int lA, int lB, int rA, int rB) {
  //Field Initializations

  leftEncoder = new encoder(lA,lB);
  rightEncoder = new encoder(rA,rB);

  //Serial.println("inside init");

  AFMS = new Adafruit_MotorShield();

  myOtherMotor = AFMS->getMotor(3);
  myMotor = AFMS->getMotor(4);

  //Serial.println("AFMS init");

  prevTime = 0;

  leftPrevEncoderPos = 0;

  leftKp = 0.15;  //0.3 (0.1 - 1)
  leftKi = 75;   //5 - 70
  leftKd = 0;   //0
  leftMotorPID = new PID(&leftVelocity, &leftPower, &leftSetpoint,leftKp,leftKi,leftKd, DIRECT);

  rightPrevEncoderPos = 0;

  rightKp = 0.15;
  rightKi = 75;
  rightKd = 0;
  rightMotorPID = new PID(&rightVelocity, &rightPower, &rightSetpoint,rightKp,rightKi,rightKd, DIRECT);

  //Serial.println("PID init");

  //Motor Initialization
  AFMS->begin();  // create with the default frequency 1.6KHz

  //myMotor->setSpeed(120);
  //myOtherMotor->setSpeed(120);
  //myMotor->run(FORWARD);
  //myOtherMotor->run(FORWARD);

  //PID Initialization
  leftMotorPID->SetSampleTime(3);
  leftMotorPID->SetMode(AUTOMATIC);
  leftMotorPID->SetOutputLimits(-255, 255);

  rightMotorPID->SetSampleTime(3);
  rightMotorPID->SetMode(AUTOMATIC);
  rightMotorPID->SetOutputLimits(-255, 255);

  //delay for testing purposes
  delay(1000);
  //Serial.println("Motor Control Initialized");
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
  else if(s == '2'){
    motorSpeed = 135;
  }
  else if(s == '3'){
    motorSpeed = 180;
  }
}

void MotorControl::setMotorDirection(char d){
  if(d == 'f'){
    motorDirection = -1;
  }
  else if(d == 'b'){
    motorDirection = 1;
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

  Serial.print("Velocity:" + String(leftVelocity) +  " / " + String(rightVelocity));
  Serial.print(" Set:" + String(leftSetpoint) + " / " + String(rightSetpoint));
  Serial.print(" Power:" + String(leftPower) +  " / " + String(rightPower) + "\n");
  Serial.print(" Set Speed:" + String(motorSpeed) +  " / Set Direction: " + String(motorDirection) + "\n");
  /* //Serial Plotter
  Serial.println(int(rightVelocity));
  Serial.println(int(leftPower));
  Serial.print(" ");
  */

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
  if(rightPower > 0 ){
    myOtherMotor->run(BACKWARD);
  }else{
    myOtherMotor->run(FORWARD);
  }
  myOtherMotor->setSpeed(abs((int)rightPower));
  //Serial.println("Set Motor Speeds");
}

int MotorControl::normalizeSpeedForAFMS(double s) {
  return (s / motorMaxSpeed) * 255;
}

void MotorControl::calculateVelocity() {
  if (vSampleCount < numVSamples) {
    unsigned long t = millis();
    Serial.println("Left Encoder Pos " + String(leftEncoder->getPos()));
    Serial.println("Time Diff " + String((t-prevTime)));

    leftVSampleSum += 2*(leftEncoder->getPos() - leftPrevEncoderPos)/(.001*double(t-prevTime));
    leftPrevEncoderPos = leftEncoder->getPos();
    rightVSampleSum += 2*(rightEncoder->getPos() - rightPrevEncoderPos)/(.001*double(t-prevTime));
    rightPrevEncoderPos = rightEncoder->getPos();
    prevTime = t;
    vSampleCount++;
  }
  if (vSampleCount == numVSamples) {
    double lv = normalizeSpeedForAFMS(leftVSampleSum / numVSamples);
    double rv = normalizeSpeedForAFMS(rightVSampleSum / numVSamples);
    if (lv != 0 ) {
      leftVelocity = lv;
    }
    if (rv != 0 ) {
      rightVelocity = rv;
    }
    leftVSampleSum = 0;
    rightVSampleSum = 0;
    vSampleCount = 0;
  }
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
