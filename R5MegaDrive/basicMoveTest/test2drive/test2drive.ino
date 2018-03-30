#include "MotorControl.h"
#include <Arduino.h>

#define DRIVE_MEGA_I2C 8

#define ENCODER_L_A 19
#define ENCODER_L_B 18
#define ENCODER_R_A 3
#define ENCODER_R_B 5

MotorControl * m;
encoder* leftEncoder;
encoder* rightEncoder;

int isrCount[2] = {0, 0};

void setup() {
  Serial.begin(115200);  // start serial for testing outputs
  delay(1000);

  //Serial.println("welcome to this test");

  initMotorControl();

  //test
  m->setMotorMode(FWD2);

  //Serial.println("end of setup - main");

  //these will halt the program and print best values when done
  //use one at a time. P, set P in MotorControl, I, set I in MotorControl
  //we can tune on the field by running this, then plug into serial to see result
  //args: (min, max, step)
  //m->sweepPValues(.1, .8, .05);
  //m->sweepIValues(15, 20, 1);
}

void loop() {
  delay(LOOP_DELAY);
  //Serial.println("left encoder isr " + String(isrCount[0]) + " / right encoder isr " + String(isrCount[1]));
  //Serial.println("left encoder position " + String(leftEncoder->getPos()) + " / right encoder position" + String(rightEncoder->getPos()));

  m->updateMotorControl();
  m->serialDebugOutput(false);    //debugging
}




//REQUIRED MAIN METHOD FUNCTIONS FOR MOTOR CONTROL BELOW

void initMotorControl() {
  m = new MotorControl(ENCODER_L_A, ENCODER_L_B, ENCODER_R_A, ENCODER_R_B);

  m->setMotorMode(STOP);

  leftEncoder = m->getLeftEncoder();
  rightEncoder = m->getRightEncoder();

  attachInterrupt(digitalPinToInterrupt(ENCODER_L_A), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R_A), rightEncoderISR, CHANGE);

  //Serial.println("motor control initialized in main");
}

void leftEncoderISR() {
  isrCount[0]++;
  leftEncoder->updatePos();
}

void rightEncoderISR() {
  isrCount[1]++;
  rightEncoder->updatePos();
}



