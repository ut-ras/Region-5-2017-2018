#include "MotorControl.h"

#define DRIVE_MEGA_I2C 8

#define ENCODER_L_A 19
#define ENCODER_L_B 18
#define ENCODER_R_A 3
#define ENCODER_R_B 5

MotorControl m(ENCODER_L_A, ENCODER_L_B, ENCODER_R_A, ENCODER_R_B);

encoder* leftEncoder;
encoder* rightEncoder;

void setup() {
  Serial.begin(9600);  // start serial for testing outputs
  initMotorControl();
  testMotorSetup();
  

}

void loop() {
  delay(5);
  m.update();

}

//test function that starts motor moving fwd
void testMotorSetup() {
  m.setMotorMode(FWD1);
}

void initMotorControl() {
  m.setMotorMode(STOP);
  leftEncoder = m.getLeftEncoder();
  rightEncoder = m.getRightEncoder();
  attachInterrupt(digitalPinToInterrupt(ENCODER_L_A), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R_A), rightEncoderISR, CHANGE);
}

void leftEncoderISR() {
  leftEncoder->updatePos();
}

void rightEncoderISR() {
  rightEncoder->updatePos();
}
