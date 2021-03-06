#include "MotorControl.h"
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

MotorControl::MotorControl(int lA, int lB, int rA, int rB) {
  //Field Initializations

  l_Encoder = new encoder(lA, lB);
  r_Encoder = new encoder(rA, rB);

  //Serial.println("inside init");

  AFMS = new Adafruit_MotorShield();

  r_Motor = AFMS->getMotor(3);
  l_Motor = AFMS->getMotor(4);

  //Serial.println("AFMS init");

  prevTime = 0;

  leftKp = .25;  //0.1 - 1
  leftKi = 15;   //5 - 70
  leftKd = 0;   //0
  l_PID = new PID(&l_EncoderSpeed, &l_PIDSpeed, &l_SetpointSpeed, leftKp, leftKi, leftKd, DIRECT);

  rightKp = 0.25;
  rightKi = 17;
  rightKd = 0;
  r_PID = new PID(&r_EncoderSpeed, &r_PIDSpeed, &r_SetpointSpeed, rightKp, rightKi, rightKd, DIRECT);

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
}

void MotorControl::turninPlace(int dir) {    //use Directions enum LEFT or RIGHT
  if (dir == RIGHT) {
    l_Motor->run(FORWARD);
    r_Motor->run(FORWARD);
  }
  else if (dir == LEFT) {
    l_Motor->run(BACKWARD);
    r_Motor->run(BACKWARD);
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

    //Serial.println("Left Encoder Diff " + String(l_Encoder->getPos() - l_PrevEncoderPos));
    //Serial.println("Time Diff " + String((t - prevTime)));

    leftVSampleSum += abs(2 * (l_Encoder->getPos() - l_PrevEncoderPos) / (.001 * double(t - prevTime)));
    l_PrevEncoderPos = l_Encoder->getPos();

    rightVSampleSum += abs(2 * (r_Encoder->getPos() - r_PrevEncoderPos) / (.001 * double(t - prevTime)));
    r_PrevEncoderPos = r_Encoder->getPos();

    prevTime = t;
    vSampleCount++;
  }
  if (vSampleCount == numVSamples) {
    //double lv = normalizeSpeedForAFMS(leftVSampleSum / numVSamples);
    //double rv = normalizeSpeedForAFMS(rightVSampleSum / numVSamples);
    double lv = (leftVSampleSum/ numVSamples);
    double rv = (rightVSampleSum/ numVSamples);

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
  r_Motor->setSpeed(r_rotSpeed);
}

int MotorControl::MotorControl::normalizeSpeedForAFMS(double s) {
  return (s / motorMaxSpeed) * 255;
}

void MotorControl::setMotorMode(int c) {
  switch (c) {
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
    Serial.print(int(r_EncoderSpeed));
    Serial.print(",");
    Serial.println(int(l_EncoderSpeed));

  }
  else {
    Serial.print(" Encoder: " +String(l_EncoderSpeed)+" / "+ String(r_EncoderSpeed));
    Serial.print(" Set: " + String(l_SetpointSpeed)+ "/ " + String(r_SetpointSpeed));
    Serial.print(" PID out: " + String(l_PIDSpeed)+ " / " +String(r_PIDSpeed) + "\n");
    Serial.println();
  }
}

//AUTOTUNING PID's (our version)

void MotorControl::sweepPValues(double minP, double maxP, double stepP) {
  setIValues(0);
  
  double r_bestP = 0;
  double l_bestP = 0;
  
  double r_minDiff = 1000;
  double l_minDiff = 1000;
  
  for(double i = minP; i<maxP; i+=stepP) {
    Serial.println("P"+String(i));
    setPValues(i);
    
    double l_avgDiff = 0;
    double r_avgDiff = 0;
    
    for (int j =0; j<100; j++) {
      updateMotorControl();
      serialDebugOutput(false);
      l_avgDiff += abs(l_EncoderSpeed - l_SetpointSpeed);
      r_avgDiff += abs(r_EncoderSpeed - r_SetpointSpeed);
      delay(LOOP_DELAY);
    }

    l_avgDiff /= 100;
    r_avgDiff /= 100;

    if (l_avgDiff < l_minDiff) {
      l_minDiff = l_avgDiff;
      l_bestP = i;
    }
    if (r_avgDiff < r_minDiff) {
      r_minDiff = r_avgDiff;
      r_bestP = i;
    }
  }
  
  setMotorMode(STOP);
  while(1) {
    Serial.println("Best P vals: L=" + String(r_bestP) + " R=" + String(l_bestP));
    delay(3000);
  }
}

void MotorControl::sweepIValues(double minI, double maxI, double stepI) {
  double r_bestI = 0;
  double l_bestI = 0;
  
  double r_minDiff = 1000;
  double l_minDiff = 1000;
  
  for(double i = minI; i<maxI; i+=stepI) {
    Serial.println("I"+String(i));
    setIValues(i);

    double l_avgDiff = 0;
    double r_avgDiff = 0;
    
    for (int i =0; i<100; i++) {
      updateMotorControl();  
      serialDebugOutput(false);    
      l_avgDiff += abs(l_EncoderSpeed - l_SetpointSpeed);
      r_avgDiff += abs(r_EncoderSpeed - r_SetpointSpeed);
      delay(LOOP_DELAY);
    }

    l_avgDiff /= 100;
    r_avgDiff /= 100;

    if (l_avgDiff < l_minDiff) {
      l_minDiff = l_avgDiff;
      l_bestI = i;
    }
    if (r_avgDiff < r_minDiff) {
      r_minDiff = r_avgDiff;
      r_bestI = i;
    }
    
    setIValues(0);
    delay(100);
  }
  
  setMotorMode(STOP);
  while(1) {
    Serial.println("Best I vals: L=" + String(r_bestI) + " R=" + String(l_bestI));
    delay(3000);
  }
}




void MotorControl::setPValues(double p_val) {
  l_PID->SetTunings(p_val, 0, 0);
  r_PID->SetTunings(p_val, 0, 0);
}

void MotorControl::setIValues(double i_val)
{
  l_PID->SetTunings(0.25, i_val, 0);
  r_PID->SetTunings(0.25, i_val, 0);
  leftKi = i_val;
  rightKi = i_val;
}


//auto tune library - not currently working
/*
void MotorControl::tunePID() {
  PID_ATune l_tunePID(&l_EncoderSpeed, &l_PIDSpeed);
  PID_ATune r_tunePID(&r_EncoderSpeed, &r_PIDSpeed);

  l_tunePID.SetNoiseBand(1);
  l_tunePID.SetOutputStep(2);
  l_tunePID.SetLookbackSec(30);
  l_tunePID.SetControlType(0);

  r_tunePID.SetNoiseBand(1);
  r_tunePID.SetOutputStep(2);
  r_tunePID.SetLookbackSec(30);
  r_tunePID.SetControlType(0);

  setMotorMode(FWD1);

  while (l_tunePID.Runtime() == 0) {
    calculateEncoderSpeeds();
    Serial.println("Auto PID Left: p=" + String(l_tunePID.GetKp()) + " i=" + String(l_tunePID.GetKp()) + " d=" + String(l_tunePID.GetKd()));
    delay(30);
  }

  leftKp = l_tunePID.GetKp();
  leftKi = l_tunePID.GetKi();
  leftKd = l_tunePID.GetKd();

  while (r_tunePID.Runtime() == 0) {
    calculateEncoderSpeeds();
    Serial.println("Auto PID Right: p=" + String(r_tunePID.GetKp()) + " i=" + String(r_tunePID.GetKp()) + " d=" + String(r_tunePID.GetKd()));
    delay(30);
  }

  rightKp = r_tunePID.GetKp();
  rightKi = r_tunePID.GetKi();
  rightKd = r_tunePID.GetKd();

  Serial.println("Auto PID Left: p=" + String(leftKp) + " i=" + String(leftKi) + " d=" + String(leftKd));
  Serial.println("Auto PID Right: p=" + String(rightKp) + " i=" + String(rightKi) + " d=" + String(rightKd));

  stopMotors();
  r_tunePID.Cancel();
  l_tunePID.Cancel();
} */

