// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

int time;
int prevTime = 0;

int leftPrevEncoderPos = 0;
double leftSetpoint, leftVelocity, leftPower;
double leftKp = 2;
double leftKi = 5;
double leftKd = 1;
PID leftMotorPID(&leftVelocity, &leftPower, &leftSetpoint,leftKp,leftKi,leftKd, DIRECT);

int rightPrevEncoderPos = 0;
double rightSetpoint, rightVelocity, rightPower;
double rightKp = 2;
double rightKi = 5;
double rightKd = 1;
PID rightMotorPID(&rightVelocity, &rightPower, &rightSetpoint,rightKp,rightKi,rightKd, DIRECT);

void velocity(int leftEncoder, int rightEncoder){
  time = 0.001*millis();
  leftVelocity = 2*(leftEncoder - leftPrevEncoderPos)/(time-prevTime); //need to linearize
  leftPrevEncoderPos = leftEncoder;
  rightVelocity = 2*(rightEncoder - rightPrevEncoderPos)/(time-prevTime); //need to linearize
  rightPrevEncoderPos = rightEncoder;
  prevTime = time;
}

void resetVelocity(){
  prevTime = 0.001*millis();
  leftPrevEncoderPos = 0;
  rightPrevEncoderPos = 0;
}

void PIDInit(){
  leftMotorPID.SetSampleTime(10);
  leftMotorPID.SetMode(AUTOMATIC);
  leftMotorPID.SetOutputLimits(-255,255);
  
  rightMotorPID.SetSampleTime(10);
  rightMotorPID.SetMode(AUTOMATIC);
  rightMotorPID.SetOutputLimits(-255,255);
}

void setSpeed(int leftSpeed, int rightSpeed){
  leftSetpoint = leftSpeed;
  leftMotorPID.Compute();
  if(leftPower < 0 ){
    myMotor->run(BACKWARD);
  }else{
    myMotor->run(FORWARD);
  }
  myMotor->setSpeed(abs((int)leftPower));

  rightSetpoint = rightSpeed;
  rightMotorPID.Compute();
    if(rightPower < 0 ){
    myOtherMotor->run(BACKWARD);
  }else{
    myOtherMotor->run(FORWARD);
  }
  myOtherMotor->setSpeed(abs((int)rightPower));
}


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  // myMotor->setSpeed(50);

  myMotor->run(FORWARD);
  myOtherMotor->run(FORWARD);
  myMotor->setSpeed(120);
  myOtherMotor->setSpeed(120);
  PIDInit();

  delay(5000);
  Serial.print("DELAYDONE");
}

void loop() {
  
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
  /*
  
  reset--;
  if(reset == 0){
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write("T");           // sends one bytes
    Wire.endTransmission();    // stop transmitting
    //Serial.print("test");
    reset = 500;
  }
    */
}


