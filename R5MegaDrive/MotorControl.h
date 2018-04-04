#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <sensorbar.h>

#include "encoder.h"
#include "arrayline.h"

#define LOOP_DELAY 100


//required libraries: Adafruit_MotorShield v2, PID by Brett, SparkFun Line Follower Array


/* HOW TO USE
 * set up encoder ISR in main for both edges of pin A and call updatePos on the encoder
 * call updateMotorControl in a loop
 * use setMotorMode, move, turn, or stop to control
 *
 * v2 of MotorControl class, motor directions and speed more straightforward
 */


enum Commands{FWD1, FWD2, FWD3, BACK1, BACK2, BACK3, LEFTIP, RIGHTIP, FWDNOLINE, LEFT45, LEFT90, LEFT135, LEFT180, RIGHT45, RIGHT90, RIGHT135, RIGHT180, STOP};    //from i2c
enum Directions{FWD, BACK, LEFT, RIGHT};

class MotorControl {

public:
  MotorControl(int lA, int lB, int rA, int rB);

  //i2c communication byte interpretation
  void setMotorMode(int c);

  void updateMotorControl();      //with PID output

  encoder* getLeftEncoder();     //use this to attatch interrupts to encoder pins in main. call updatePos in ISR
  encoder* getRightEncoder();

  void moveStraight(int dir);             //use Directions enum FWD or BACK
  void turninPlace(int dir);   //use Directions enum LEFT or RIGHT
  void stopMotors();

  //set desired speeds for PID
  void setSetpointSpeeds(int rotSpeed);                     //deg / sec
  void setSetpointSpeeds(int l_rotSpeed, int r_rotSpeed);   //deg / sec

  void serialDebugOutput(boolean plotter);

  //PID tuning
  void setPValues(double p_val);
  void setIValues(double i_val);

  void sweepPValues(double minP, double maxP, double stepP);
  void sweepIValues(double minI, double maxI, double stepI);

  //turn maneuver
  void turnManeuver(int dir, int num45Deg);
  void moveStraightEncoderTicks(int dir, int encoderTicks);		//move fwd along lines an exact number of encoder encoderTicks
  void turnEncoderTicks(int dir, int encoderTicks);    //use Directions enum LEFT or RIGHT


private:

  //updateMotorSpeeds functions
  void calculateLSCorrections();
  void calculateEncoderSpeeds();
  void calculatePIDSpeeds();
  void setMotorSpeeds(int l_rotSpeed, int r_rotSpeed);    //set actual speeds, direct output to AFMS motors

  int currentCmd;

  //hardware
  Adafruit_MotorShield *AFMS;
  Adafruit_DCMotor *l_Motor;
  Adafruit_DCMotor *r_Motor;
  encoder* l_Encoder;
  encoder* r_Encoder;
  arrayline* lineSensorBack;
  arrayline* lineSensorFront;

  // PID Variables
  PID * l_PID;
  PID * r_PID;
  double leftKp, leftKi, leftKd;
  double rightKp, rightKi, rightKd;

  // rotational speeds between 0 and 255 (deg / sec)
  double  l_EncoderSpeed, r_EncoderSpeed;    //PID input, calculated speed of motors
  double l_SetpointSpeed, r_SetpointSpeed;       //desired v of motors, for PID
  double  l_PIDSpeed, r_PIDSpeed;        //PID output, actual speed input to the motors to reach desired v

  //line sensor correction
  int l_correction, r_correction;
  bool useArray = false;
  int startTicks = 0;

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
