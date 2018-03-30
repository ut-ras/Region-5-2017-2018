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
  initI2c();

  //these will halt the program and print best values when done
  //use one at a time. P, set P in MotorControl, I, set I in MotorControl
  //we can tune on the field by running this, then plug into serial to see result
  //args: (min, max, step)
  //m->sweepPValues(.1, .8, .05);
  //m->sweepIValues(15, 20, 1);

  Serial.println("end of setup - drive mega main");


  //test
  m->setMotorMode(FWD2);
}

void loop() {
  //test different loop delays, LOOP_DELAY in MotorControl.h
  delay(LOOP_DELAY);

  m->updateMotorControl();
  m->serialDebugOutput(false);    //debugging

  //encoder check
  //Serial.println("left encoder isr " + String(isrCount[0]) + " / right encoder isr " + String(isrCount[1]));
  //Serial.println("left encoder position " + String(leftEncoder->getPos()) + " / right encoder position" + String(rightEncoder->getPos()));
}




//REQUIRED MAIN METHOD FUNCTIONS FOR MOTOR CONTROL BELOW

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) {   // loop through all but the last
    char c = Wire.read();      // receive byte as a character
    m->setMotorMode(c);
  }
}

void initI2c() {
  //I2C Initialization
  //Wire.begin();        //i dont think we need this
  Wire.begin(DRIVE_MEGA_I2C);
  Wire.onReceive(receiveEvent);
}

void initMotorControl() {
  m = new MotorControl(ENCODER_L_A, ENCODER_L_B, ENCODER_R_A, ENCODER_R_B);

  m->setMotorMode(STOP);

  leftEncoder = m->getLeftEncoder();
  rightEncoder = m->getRightEncoder();

  attachInterrupt(digitalPinToInterrupt(ENCODER_L_A), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R_A), rightEncoderISR, CHANGE);

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
