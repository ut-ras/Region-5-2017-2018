#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "encoder.h"

//required libraries: Adafruit_MotorShield v2, PID by Brett


/* HOW TO USE
 * set up encoder ISR in main for both edges of pin A and call updatePos on the encoder
 * call updateMotorControl in a loop
 * use setMotorMode, move, turn, or stop to control
 * 
 * v2 of MotorControl class, motor directions and speed more straightforward
 */


enum Commands{FWD1, FWD2, FWD3, BACK1, BACK2, BACK3, LEFTIP, RIGHTIP, STOP};    //from i2c
enum Directions{FWD, BACK, LEFT, RIGHT};

class MotorControl {

public:
  MotorControl(int lA, int lB, int rA, int rB);

  //i2c communication byte interpretation
  void setMotorMode(int c);

  void updateMotorControl();      //with PID output
  void updateMotorControlLine(int dir);   //TODO add line following to updateMotorControl

  encoder* getLeftEncoder();     //use this to attatch interrupts to encoder pins in main. call updatePos in ISR
  encoder* getRightEncoder();

  void moveStraight(int dir);             //use Directions enum FWD or BACK
  void turninPlace(int dir);   //use Directions enum LEFT or RIGHT
  void stopMotors();

  //set desired speeds for PID
  void setSetpointSpeeds(int rotSpeed);                     //deg / sec
  void setSetpointSpeeds(int l_rotSpeed, int r_rotSpeed);   //deg / sec

  void serialDebugOutput(boolean plotter);

private:

  //updateMotorSpeeds functions
  void calculateEncoderSpeeds();
  void calculatePIDSpeeds();
  void setMotorSpeeds(int l_rotSpeed, int r_rotSpeed);    //set actual speeds, direct output to AFMS motors
  int normalizeSpeedForAFMS(double s);

  //hardware
  Adafruit_MotorShield *AFMS;
  Adafruit_DCMotor *l_Motor;
  Adafruit_DCMotor *r_Motor;
  encoder* l_Encoder;
  encoder* r_Encoder;

  // PID Variables
  PID * l_PID;
  PID * r_PID;
  double leftKp, leftKi, leftKd;
  double rightKp, rightKi, rightKd;

  // rotational speeds between 0 and 255 (deg / sec)
  double  l_EncoderSpeed, r_EncoderSpeed;    //PID input, calculated speed of motors
  double l_SetpointSpeed, r_SetpointSpeed;       //desired v of motors, for PID
  double  l_PIDSpeed, r_PIDSpeed;        //PID output, actual speed input to the motors to reach desired v

  //encoder vars
  int l_PrevEncoderPos = 0;      //encoder steps
  int r_PrevEncoderPos = 0;
  unsigned long prevTime;   //stored as milliseconds, converted to second in calculateVelocity

  // velocity averaging vars
  const double numVSamples = 1.0;
  int vSampleCount = 0;
  double leftVSampleSum = 0;
  double rightVSampleSum = 0;

  //constants
  const double motorMaxSpeed = 950.0;     //deg / sec

};

#endif
