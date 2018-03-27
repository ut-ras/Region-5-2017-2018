#include <Wire.h>
#include "MotorControl.h"
#include "arrayline.h"
#define DRIVE_MEGA_I2C 8

#define ENCODER_L_A 2
#define ENCODER_L_B 4
#define ENCODER_R_A 3
#define ENCODER_R_B 5

MotorControl m(ENCODER_L_A, ENCODER_L_B, ENCODER_R_A, ENCODER_R_B);

encoder* leftEncoder;
encoder* rightEncoder;
arrayline* lineArray;

void setup() {
  Serial.begin(9600);  // start serial for testing outputs

  initI2c();
  initMotorControl() ;
  testMotorSetup();     //test function that starts motor moving fwd
}

void initI2c() {
  //I2C Initialization
  //Wire.begin();        //i dont think we need this
  Wire.begin(DRIVE_MEGA_I2C);
  Wire.onReceive(receiveEvent);
}
void initArrayLine()
{
  lineArray = new arrayline();
}
void initMotorControl() {
  m.setMotorMode(STOP);
  leftEncoder = m.getLeftEncoder();
  rightEncoder = m.getRightEncoder();
  attachInterrupt(digitalPinToInterrupt(ENCODER_L_A), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R_A), rightEncoderISR, CHANGE);
}

void loop() {
  delay(5);
  m.update();
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) {   // loop through all but the last
    char c = Wire.read();      // receive byte as a character
    m.setMotorMode(c);
  }
}

void leftEncoderISR() {
  leftEncoder->updatePos();
}

void rightEncoderISR() {
  rightEncoder->updatePos();
}



//test function that starts motor moving fwd
void testMotorSetup() {
  m.setMotorMode(FWD1);
}
