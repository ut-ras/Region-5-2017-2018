#ifndef MOTORCONTROL_H

class MotorControl {

public:
  MotorControl();
  void move(bool fwd);
  void turn(bool left);
  void stop();

private:
  void setSpeed(int s);
  void calculateVelocity();

  //Motor Variables
  
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
}
