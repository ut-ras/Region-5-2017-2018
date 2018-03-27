#include "MotorControl.h"
#include <Arduino.h>
#include "digitalWriteFast.h"

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
  Serial.println("welcome to this test");

  initMotorControl();
  testMotorSetup();
  Serial.println("end of setup - main");

}

void loop() {
  delay(20);
  //Serial.println("left encoder isr " + String(isrCount[0]) + " / right encoder isr " + String(isrCount[1]));
  Serial.println("left encoder position " + String(leftEncoder->getPos()) + " / right encoder position" + String(rightEncoder->getPos())); 
  m->update();
}

//test function that starts motor moving fwd
void testMotorSetup() {
  m->setMotorMode(FWD1);
}

void initMotorControl() {
  m = new MotorControl(ENCODER_L_A, ENCODER_L_B, ENCODER_R_A, ENCODER_R_B);

  m->setMotorMode(STOP);
  
  leftEncoder = m->getLeftEncoder();
  rightEncoder = m->getRightEncoder();


  attachInterrupt(digitalPinToInterrupt(ENCODER_L_A), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R_A), rightEncoderISR, RISING);
  Serial.println("motor control initialized in main");
}

void leftEncoderISR() {
  isrCount[0]++;
  leftEncoder->updatePos();
}

void rightEncoderISR() {
  isrCount[1]++;
  rightEncoder->updatePos();
}

