#include "MotorControl.h"
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

MotorControl::MotorControl(int lA, int lB, int rA, int rB) {
  //Field Initializations

  l_Encoder = new encoder(lA,lB);
  r_Encoder = new encoder(rA,rB);

  //Serial.println("inside init");

  AFMS = new Adafruit_MotorShield();

  r_Motor = AFMS->getMotor(3);
  l_Motor = AFMS->getMotor(4);

  //Serial.println("AFMS init");

  prevTime = 0;

  leftKp = 0.0;  //0.3 (0.1 - 1)
  leftKi = 0;   //5 - 70
  leftKd = 0;   //0
  l_PID = new PID(&l_EncoderSpeed, &l_PIDSpeed, &l_SetpointSpeed, leftKp,leftKi,leftKd, DIRECT);

  rightKp = 0.0;
  rightKi = 0;
  rightKd = 0;
  r_PID = new PID(&r_EncoderSpeed, &r_PIDSpeed, &r_SetpointSpeed, rightKp,rightKi,rightKd, DIRECT);

  //Serial.println("PID init");

  //Motor Initialization
  AFMS->begin();  // create with the default frequency 1.6KHz

  l_Motor->setSpeed(120);
  r_Motor->setSpeed(120);
  l_PIDSpeed = 120;
  r_PIDSpeed = 120;
  
  //PID Initialization
  l_PID->SetSampleTime(3);
  l_PID->SetMode(AUTOMATIC);
  l_PID->SetOutputLimits(0, 255);

  r_PID->SetSampleTime(3);
  r_PID->SetMode(AUTOMATIC);
  r_PID->SetOutputLimits(0, 255);

  //delay for testing purposes
  delay(500);
  //Serial.println("Motor Control Initialized");
}


//Public Functions

encoder* MotorControl::getLeftEncoder() {
  return l_Encoder;
}

encoder* MotorControl::getRightEncoder() {
  return r_Encoder;
}

void MotorControl::updateMotorControl() {      //update motor speeds with PID
  calculateEncoderSpeeds();
  calculatePIDSpeeds();
  setMotorSpeeds(abs(l_PIDSpeed), abs(r_PIDSpeed));

  //debugging
  serialDebugOutput(false);
}

void MotorControl::turninPlace(int dir) {    //use Directions enum LEFT or RIGHT
  if (dir == RIGHT) {
    l_Motor->run(BACKWARD);
    r_Motor->run(BACKWARD);
  }
  else if (dir == LEFT) {
    l_Motor->run(FORWARD);
    r_Motor->run(FORWARD);
  }
}

void MotorControl::moveStraight(int dir) {              //use Directions enum FWD or BACK
  if (dir == FWD) {
    l_Motor->run(BACKWARD);
    r_Motor->run(FORWARD);
  }
  else if (dir == BACK) {
    l_Motor->run(FORWARD);
    r_Motor->run(BACKWARD);
  }
}

void MotorControl::stopMotors() {
  setMotorSpeeds(0, 0);
}



//Private Functions

//set desired speeds
void MotorControl::setSetpointSpeeds(int rotSpeed) {                      //deg / sec
  setSetpointSpeeds(rotSpeed, rotSpeed);
}

void MotorControl::setSetpointSpeeds(int l_rotSpeed, int r_rotSpeed) {    //deg / sec
  l_SetpointSpeed = l_rotSpeed;
  r_SetpointSpeed = r_rotSpeed;
}

//updateMotorSpeeds functions
void MotorControl::calculateEncoderSpeeds() {
  if (vSampleCount < numVSamples) {
    unsigned long t = millis();

    //Serial.print("Left Encoder Diff " + String(l_Encoder->getPos() - l_PrevEncoderPos));
    //Serial.print(" Time Diff " + String((t-prevTime)));

    leftVSampleSum += abs(2*(l_Encoder->getPos() - l_PrevEncoderPos)/(.001*double(t-prevTime)));
    l_PrevEncoderPos = l_Encoder->getPos();

    rightVSampleSum += abs(2*(r_Encoder->getPos() - r_PrevEncoderPos)/(.001*double(t-prevTime)));
    r_PrevEncoderPos = r_Encoder->getPos();

    prevTime = t;
    vSampleCount++;
  }
  if (vSampleCount == numVSamples) {
    //double lv = normalizeSpeedForAFMS(leftVSampleSum / numVSamples);
    //double rv = normalizeSpeedForAFMS(rightVSampleSum / numVSamples);
    double lv = (leftVSampleSum/ numVSamples);
    double rv = (rightVSampleSum/ numVSamples);

    //avoid bad values

      l_EncoderSpeed = lv;
      r_EncoderSpeed = rv; 
    

    
    leftVSampleSum = 0;
    rightVSampleSum = 0;
    vSampleCount = 0;
  }
}
void MotorControl::calculatePIDSpeeds() {
  l_PID->Compute();
  r_PID->Compute();
}
void MotorControl::setMotorSpeeds(int l_rotSpeed, int r_rotSpeed) {     //set actual speeds, direct output to AFMS motors
  l_Motor->setSpeed(l_rotSpeed);
  r_Motor->setSpeed(l_rotSpeed);
}

int MotorControl::MotorControl::normalizeSpeedForAFMS(double s) {
  return (s / motorMaxSpeed) * 255;
}

void MotorControl::setMotorMode(int c) {
  switch(c){
    case FWD1:
      setSetpointSpeeds(90);
      moveStraight(FWD);
      break;
    case FWD2:
      setSetpointSpeeds(135);
      moveStraight(FWD);
      break;
    case FWD3:
      setSetpointSpeeds(180);
      moveStraight(FWD);
      break;
    case BACK1:
      setSetpointSpeeds(90);
      moveStraight(BACK);
      break;
    case BACK2:
      setSetpointSpeeds(135);
      moveStraight(BACK);
      break;
    case BACK3:
      setSetpointSpeeds(180);
      moveStraight(BACK);
      break;
    case LEFTIP:
      setSetpointSpeeds(90);
      turninPlace(LEFT);
      break;
    case RIGHTIP:
      setSetpointSpeeds(90);
      turninPlace(RIGHT);
      break;
    case STOP:
      stopMotors();
      break;
  }
}

void MotorControl::serialDebugOutput(bool plotter) {
  if (plotter) {
    //Serial.println(int(l_EncoderSpeed));
    Serial.println(int(l_PIDSpeed));
    Serial.print(" ");
  }
  else {
    Serial.print(String(l_EncoderSpeed) +  "  " + String(r_EncoderSpeed));
   // Serial.print(" Set:" + String(l_SetpointSpeed) + " / " + String(r_SetpointSpeed));
    //Serial.print(" PID out:" + String(l_PIDSpeed) +  " / " + String(r_PIDSpeed) + "\n");
    Serial.println();
  }
}

void MotorControl::setPValues(double p_val)
{
  l_PID->SetTunings(p_val, 0, 0);
  r_PID->SetTunings(p_val, 0, 0);
}

