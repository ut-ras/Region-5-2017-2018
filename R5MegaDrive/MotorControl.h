#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "encoder.h"

//required libraries:
//Adafruit_MotorShield v2
//PID by Brett

enum Commands{m1f, m2f, m3f, m1b, m2b, m3b, t1f, t1b, s};

class MotorControl {

public:
  MotorControl(int lA, int lB, int rA, int rB);
  void update();
  void setMotorMode(int c);

  encoder* getLeftEncoder();
  encoder* getRightEncoder();

private:

  void setMotorAction(char a);
  void setMotorSpeed(char s);
  void setMotorDirection(char d);

  void setPIDSpeed(int leftSpeed, int rightSpeed);
  void calculateVelocity();

  //Motor Variables

  char motorAction;
  int motorSpeed;
  int motorDirection;

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
