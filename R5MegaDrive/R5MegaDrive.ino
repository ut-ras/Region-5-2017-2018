#include <Wire.h>
#include "MotorControl.h"

#define leftA 2

MotorControl m(2, 4, 3, 5);

encoder* leftEncoder;
encoder* rightEncoder;

void setup() {
  m.setMotorMode(s);

  //I2C Initialization
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  leftEncoder = m.getLeftEncoder();
  rightEncoder = m.getRightEncoder();
  
  attachInterrupt(digitalPinToInterrupt(2), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), rightEncoderISR, CHANGE);

  testMotorSetup();
}

void loop() {
  delay(5);
  m.update();
}

void testMotorSetup() {
  m.setMotorMode(m1f);
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


