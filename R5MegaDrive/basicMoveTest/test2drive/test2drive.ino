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
  m->setMotorMode(FWD1);

  //Serial.println("end of setup - main");

  //tests
  //m->tunePID(); doesnt work right now
  m->setMotorMode(BACK2);
}

void loop() {
  delay(100);
  //Serial.println("left encoder isr " + String(isrCount[0]) + " / right encoder isr " + String(isrCount[1]));
  //Serial.println("left encoder position " + String(leftEncoder->getPos()) + " / right encoder position" + String(rightEncoder->getPos()));

  m->updateMotorControl();
  m->serialDebugOutput(false);    //debugging

    //sweepPValues();

}


void sweepPValues()
{
  for(double i = 0; i<1; i+=.1)
  {
    Serial.println("P"+String(i));
    m->setPValues(i);
    for (int i =0; i<100; i++)
  {
    m->updateMotorControl();
    delay(10);
  }
  }
  Serial.println("Done");
}

//REQUIRED MAIN METHOD FUNCTIONS FOR MOTOR CONTROL

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
