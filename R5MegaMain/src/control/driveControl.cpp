#include <Wire.h>
#include "driveControl.h"
#include "Graph.h"
#include "intersectionSensors.h"

driveControl::driveControl(Graph * m) {
  //only do this if i2c not already started
  mapGraph = m;
  linesensors = new intersectionSensors(mapGraph, L0PIN, L1PIN, L2PIN, R0PIN, R1PIN, R2PIN);
  speed = 1;
}

void driveControl::testSendCommand() {
    for(int i =0; i<255; i++) {
      sendCommand(i);
    }
}

void driveControl::sendCommand(uint8_t command) {
  Serial.println("command: " + String(command));
  Wire.beginTransmission(DRIVE_MEGA_I2C);
  Wire.write(command);
  Wire.endTransmission();
}


//Basic Move Commands

//1 2 or 3
void driveControl::move(bool fwd) {
  if (fwd) {
    sendCommand(FWD1 + speed - 1);
  }
  else {
    sendCommand(BACK1 + speed - 1);
  }
}

void driveControl::turnManeuver(bool left, int steps) {
  Serial.println("In turnManeuver " + String(left?"left":"right"));
  sendCommand(left?(LEFT45 + steps - 1):(RIGHT45 + steps - 1));
  delay(3000);   //wait to finish turning!!!
}

void driveControl::stop() {
  sendCommand(STOP);
}

void driveControl::forwardAtStart() {
  sendCommand(FWDNOLINE);
  pointlineData next = linesensors->getPointlineFor(green, 4); //should emulate crossing the lines
  pointlineData current;
  Serial.println("next " + String(linesensors->PLDatatoString(next)));
  delay(1000);  //allow pointline sensors to get past the current intersection before polling
  
  while((current = linesensors->getDataOverTimeRolling(300)) != next) {
    Serial.println("current " + String(linesensors->PLDatatoString(current)));
   delay(5);
  }
  stop();
}

void driveControl::forwardAcrossGrey() {
  pointlineData next = linesensors->createPointlineData(0, 0, 1, 0, 0, 1); //should emulate crossing the lines
  if (mapGraph->getCurrentDirection() % 2 == 0) {
    next = linesensors->createPointlineData(0, 1, 0, 0, 1, 0); //should emulate crossing the lines
  }

  sendCommand(FWDNOLINE);

  pointlineData current;
  Serial.println("next " + String(linesensors->PLDatatoString(next)));
  delay(500);  //allow pointline sensors to get past the current intersection before polling
  
  while((current = linesensors->getDataOverTimeRolling(300)) != next) {
    Serial.println("current " + String(linesensors->PLDatatoString(current)));
   delay(5);
  }
  stop();
}


//Complex Move Commands

void driveControl::forwardToIntersection() {
  move(true);
  pointlineData next = linesensors->getNextIntersection();
  pointlineData current;
  Serial.println("next " + String(linesensors->PLDatatoString(next)));
  delay(1000);  //allow pointline sensors to get past the current intersection before polling
  while((current = linesensors->getDataOverTimeRolling(300)) != next) {
    Serial.println("current " + String(linesensors->PLDatatoString(current)));
    
    if (current.isLine()) {
      Serial.println("Near an intersection, lowering speed");
      setSpeed(1);
      move(true);
    }
    
    delay(5);
  }
  stop();
  Serial.println("found intersection:  " + String(linesensors->PLDatatoString(current)));

  delay(100);

  //back up after overshoot
  
  if ((current = linesensors->getDataOverTime(50)) != next) {
    setSpeed(1);
    move(false);

    int timeout = millis() + 1000;
    while((millis() < timeout) && ((current = linesensors->getDataOverTimeRolling(100)) != next)) {
      delay(5);
    }
    stop();
    Serial.println("found intersection: " + String(linesensors->PLDatatoString(current)));
  }
  
  mapGraph->setCurrentNode(mapGraph->getNextIntersection());
}


//increments of 45 deg, based on intersection sensors
void driveControl::turn45(bool left, int steps) {
  Serial.println("In turn45");
  if (steps >= 4 || steps <= 0) {
    return;
  }
  turnManeuver(left, steps);
  int nextDir = (mapGraph->getCurrentDirection() + steps) % 8;
  mapGraph->setCurrentDirection(nextDir);
}

void driveControl::turnTo(int dir) {
  if (dir >= 8 || dir <= 0) {
    return;
  }

  pointlineData next = linesensors->getTurnToIntersection(dir);

  bool left = true;
  int diff = mapGraph->getCurrentDirection() - dir;
  if (diff >= 4 || ((diff < 0) && (diff >= -4))) {
    left = false;
  }

  turnManeuver(left, abs(diff));
  mapGraph->setCurrentDirection(dir);
}



void driveControl::setSpeed(int s) {
  speed = s;
}

int driveControl::getSpeed() {
  return speed;
}

intersectionSensors * driveControl::getIntersectionSensors() {
  return linesensors;
}
