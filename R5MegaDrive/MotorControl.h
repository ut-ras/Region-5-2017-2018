#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class MotorControl {

public:
  MotorControl();
  void update();
  void setMotorAction();
  void setMotorSpeed();
  void setMotorDirection();

private:
  void setPIDSpeed(int leftSpeed, int rightSpeed);
  void calculateVelocity();
  
  //Motor Variables

  char motorAction;
  int motorSpeed;
  int motorDirection;
  
  encoder* leftEncoder;
  encoder* rightEncoder;
  
  Adafruit_MotorShield AFMS;

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
  PID leftMotorPID;

  int rightPrevEncoderPos;
  double rightSetpoint, rightVelocity, rightPower;
  double rightKp;
  double rightKi;
  double rightKd;
  PID rightMotorPID;
};

#endif
