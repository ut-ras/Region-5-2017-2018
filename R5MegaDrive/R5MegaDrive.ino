#include <Wire.h>
#include "MotorControl.h"

MotorControl m;

void setup() {
  m.setMotorAction(s);
  m.setMotorSpeed(1);
  m.setMotorDirection(f);
  
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
      case m1f:
        m.setMotorAction(m);
        m.setMotorSpeed(1);
        m.setMotorDirection(f);
        break;
      case m2f:
        m.setMotorAction(m);
        m.setMotorSpeed(2);
        m.setMotorDirection(f);        
        break;
      case m3f:
        m.setMotorAction(m);
        m.setMotorSpeed(3);
        m.setMotorDirection(f);
        break;
      case m1b:
        m.setMotorAction(m);
        m.setMotorSpeed(1);
        m.setMotorDirection(b);        
        break;
      case m2b:
        m.setMotorAction(m);
        m.setMotorSpeed(2);
        m.setMotorDirection(b);        
        break;
      case m3b:
        m.setMotorAction(m);
        m.setMotorSpeed(3);
        m.setMotorDirection(b);        
        break;
      case t1f:
        m.setMotorAction(t);
        m.setMotorSpeed(1);
        m.setMotorDirection(f);        
        break;
      case t1b:
        m.setMotorAction(t);
        m.setMotorSpeed(1);
        m.setMotorDirection(b);        
        break;
      case s:
        m.setMotorAction(s);        
        break;
    }
  }
}


