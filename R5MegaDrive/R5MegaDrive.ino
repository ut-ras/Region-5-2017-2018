
#include "MotorControl.h"
#include <Arduino.h>

//required libraries: Adafruit_MotorShield v2, PID by Brett, SparkFun Line Follower Array, QTRSensors

#define DRIVE_MEGA_I2C 8

#define ENCODER_L_A 3
#define ENCODER_L_B 2
#define ENCODER_R_A 19
#define ENCODER_R_B 18

MotorControl * m;
encoder* leftEncoder;
encoder* rightEncoder;
void  initMotorControl();
void  initI2c();
//int isrCount[2] = {0, 0};
int8_t newCommand = -1;


const int stopButton = 51;
const int startButton = 52;


void checkStop() {
  if (digitalRead(stopButton) == 0) {
    Serial.println("Stop button");
    m->setMotorSpeeds(0, 0);
    while(true);
  }
  Serial.println("Not Stop Button");
}

void setup() {
  Serial.begin(9600);  // start serial for testing outputs
  delay(1000);

  pinMode(stopButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);

  Serial.println("welcome to this test");

  initI2c();

  initMotorControl();
  Serial.println("setup i2c");

  //these will halt the program and print best values when done
  //use one at a time. P, set P in MotorControl, I, set I in MotorControl
  //we can tune on the field by running this, then plug into serial to see result
  //args: (min, max, step)
  //m->sweepPValues(.1, .8, .05);
  //m->sweepIValues(15, 20, 1);

  Serial.println("end of setup - drive mega main");


  //test
  m->setMotorMode(STOP);

  emergencyRound1();
}

void loop() {
  //test different loop delays, LOOP_DELAY in MotorControl.h
  checkStop();
  delay(LOOP_DELAY);

  m->updateMotorControl();
  m->serialDebugOutput(false);    //debugging

  //encoder check
  //Serial.println("left encoder isr " + String(isrCount[0]) + " / right encoder isr " + String(isrCount[1]));
  //Serial.println("left encoder position " + String(leftEncoder->getPos()) + " / right encoder position" + String(rightEncoder->getPos()));

  checkStop();
  
  if (newCommand >= 0) {
    Serial.println("New Command: " + String(newCommand));
    m->setMotorMode(newCommand);
    newCommand = -1;
  }
  
}


void emergencyRound1() {
  int wait = 15000;
  
  Serial.println("Hello");
  while(digitalRead(startButton) == 1){
    delay(100);
    checkStop();
  }

  m->setMotorMode(FWDNOLINE);
  long t = millis() + wait;
  Serial.println("FWD");  
  while(millis() < t) {
    checkStop();
    m->updateMotorControl();
    delay(LOOP_DELAY);
  }
  
  m->setMotorMode(STOP);
   t = millis() + wait - 1000;
  Serial.println("STOP");
  while(millis() < t) {
    checkStop();
    m->updateMotorControl();
    delay(LOOP_DELAY);
  }

  m->setMotorMode(BACKNOLINE);
   t = millis() + wait - 500;
   Serial.println("BACK");
  while(millis() < t) {
    checkStop();
    m->updateMotorControl();
    delay(LOOP_DELAY);
  }
  m->setMotorMode(STOP);

  Serial.println("Hello");
}



//REQUIRED MAIN METHOD FUNCTIONS FOR MOTOR CONTROL BELOW

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    Serial.println("recieve");
    int8_t c = Wire.read();      // receive byte as a character
    newCommand = c;
}

void initI2c() {
  //I2C Initialization
  Wire.begin(DRIVE_MEGA_I2C);
  Wire.onReceive(receiveEvent);
}

void initMotorControl() {
  m = new MotorControl(ENCODER_L_A, ENCODER_L_B, ENCODER_R_A, ENCODER_R_B);
  Serial.println("created motor control");
  m->setMotorMode(STOP);

  leftEncoder = m->getLeftEncoder();
  rightEncoder = m->getRightEncoder();

  attachInterrupt(digitalPinToInterrupt(ENCODER_L_A), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R_A), rightEncoderISR, CHANGE);

  Serial.println("motor control initialized in main");
}

void leftEncoderISR() {
  //isrCount[0]++;
  leftEncoder->updatePos();
}

void rightEncoderISR() {
  //isrCount[1]++;
  rightEncoder->updatePos();
}

