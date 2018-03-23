#include <Wire.h>
#include "MotorControl.h"

MotorControl m;

void setup() {
  //I2C Initialization
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
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


