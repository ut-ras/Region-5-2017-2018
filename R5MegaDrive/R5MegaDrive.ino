#include <Wire.h>
#include "MotorControl.h"

enum Commands{m1f, m2f, m3f, m1b, m2b, m3b, t1f, t1b, s};

MotorControl m;

void setup() {
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
  m.move(true);
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) {   // loop through all but the last
    char c = Wire.read();      // receive byte as a character

    switch(c){
      case m:

        break;
      case m:

        break;
      case m:

        break;
      case m:

        break;
      case m:

        break;
      case m:

        break;
      case m:

        break;




    }
  }
}
