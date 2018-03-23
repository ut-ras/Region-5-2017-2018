// Code for the enconder working as a slave

#include <Wire.h>
#include <digitalWriteFast.h>

#define leftMotorA  2
#define leftMotorB  4
#define rightMotorA 3
#define rightMotorB 5
#define I2C         8

unsigned char leftState;
unsigned char leftPreviousState;
int16_t leftPosition = 0;
unsigned char rightState;
unsigned char rightPreviousState;
int16_t rightPosition = 0;
byte buf[4];
  
void setup() {
  pinModeFast(leftMotorA,INPUT);
  pinModeFast(leftMotorB,INPUT);
  pinModeFast(rightMotorA,INPUT);
  pinModeFast(rightMotorB,INPUT);
  attachInterrupt(digitalPinToInterrupt(leftMotorA), leftUpdate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightMotorA), rightUpdate, CHANGE);
  Serial.begin(9600);

  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
 
}

void leftUpdate(){
  switch(digitalReadFast(leftMotorA)){
    case 0:
      if(digitalReadFast(leftMotorB))leftPosition++;
      else leftPosition--;
      break;
    case 1:
      if(digitalReadFast(leftMotorB))leftPosition--;
      else leftPosition++;
      break;
    }
}

void rightUpdate(){
  switch(digitalReadFast(rightMotorA)){
    case 0:
      if(digitalReadFast(rightMotorB))rightPosition++;
      else rightPosition--;
      break;
    case 1:
      if(digitalReadFast(rightMotorB))rightPosition--;
      else rightPosition++;
      break;
  }
}

void requestEvent() { 
  buf[0]= highByte(leftPosition);        // Left Motor First Byte
  buf[1]= lowByte(leftPosition);         // Left Motor Second Byte
  buf[2]= highByte(rightPosition);       // Right Motor First Byte
  buf[3]= lowByte(rightPosition);        // Right Motor Second Byte  
  Wire.write(buf,4);
 }

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  leftPosition = 0;
  rightPosition = 0;
  while (Wire.available()) {   // loop through all but the last
    char c = Wire.read();      // receive byte as a character
    Serial.print(c);           // print the character
  }
}

