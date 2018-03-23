#include <Wire.h>
#include "MotorControl.h"

MotorControl m;

void setup() {
  m.setMotorMode(s);

  //I2C Initialization
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  Wire.begin(8);
  Wire.onReceive(receiveEvent);

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
