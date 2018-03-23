#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "encoder.h"

//required libraries:
//Adafruit_MotorShield v2
//PID by Brett


class MotorControl {

public:
  MotorControl();
  void move(bool fwd);
  void turn(bool left);
  void stop();
  void update();

private:
  void setSpeed(int leftSpeed, int rightSpeed);
  void calculateVelocity();
  
  

  //Motor Variables

  encoder* leftEncoder;
  encoder* rightEncoder;
  
  Adafruit_MotorShield *AFMS;

  Adafruit_DCMotor *myMotor;
  Adafruit_DCMotor *myOtherMotor;

  //PID Variables
  int time;
  int prevTime;

  int leftPrevEncoderPos;
  double leftSetpoint, leftVelocity, leftPower;
  double leftKp;
  double leftKi;
  double leftKd;
  PID * leftMotorPID;

  int rightPrevEncoderPos;
  double rightSetpoint, rightVelocity, rightPower;
  double rightKp;
  double rightKi;
  double rightKd;
  PID * rightMotorPID;
};

#endif
