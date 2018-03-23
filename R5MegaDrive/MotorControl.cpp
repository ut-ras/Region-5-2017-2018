
#include "MotorControl.h"

MotorControl::MotorControl() {
  //Field Initializations
  Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

  Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
  Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
  
  int prevTime = 0;

  int leftPrevEncoderPos = 0;
  
  double leftKp = 2;
  double leftKi = 5;
  double leftKd = 1;
  PID leftMotorPID(&leftVelocity, &leftPower, &leftSetpoint,leftKp,leftKi,leftKd, DIRECT);

  int rightPrevEncoderPos = 0;
  
  double rightKp = 2;
  double rightKi = 5;
  double rightKd = 1;
  PID rightMotorPID(&rightVelocity, &rightPower, &rightSetpoint,rightKp,rightKi,rightKd, DIRECT);
  
  //I2C Initialization
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  //Motor Initialization
  AFMS.begin();  // create with the default frequency 1.6KHz
  
  myMotor->run(FORWARD);
  myOtherMotor->run(FORWARD);
  myMotor->setSpeed(120);
  myOtherMotor->setSpeed(120);
  PIDInit();

  //PID Initialization
  leftMotorPID.SetSampleTime(10);
  leftMotorPID.SetMode(AUTOMATIC);
  leftMotorPID.SetOutputLimits(-255,255);
  
  rightMotorPID.SetSampleTime(10);
  rightMotorPID.SetMode(AUTOMATIC);
  rightMotorPID.SetOutputLimits(-255,255);

  //delay for testing purposes
  delay(5000);
  Serial.print("DELAYDONE");
}

void MotorControl::update(){
  byte leftHigh,leftLow,rightHigh,rightLow;
  int16_t leftPosition,rightPosition;
  Wire.requestFrom(8,4);    // request 2 bytes from slave device #8
  leftHigh = Wire.read();
  leftLow = Wire.read();
  rightHigh = Wire.read();
  rightLow = Wire.read();
  
  leftPosition = word(leftHigh,leftLow);
  rightPosition = word(rightHigh,rightLow);
  Serial.print(leftPosition);
  Serial.print(", ");
  Serial.print(rightPosition);
  Serial.print("\n");

  velocity(leftPosition,rightPosition);
  setSpeed(90,90);
}

void MotorControl::move(bool fwd) {

}

void MotorControl::turn(bool left) {

}

void MotorControl::stop() {

}

void MotorControl::setSpeed(int s) {

}

void MotorControl::calculateVelocity() {

}
