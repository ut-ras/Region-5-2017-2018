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

void driveControl::sendCommand(int command) {
  Serial.println("cmd: " + String(command));
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
  sendCommand(left?(LEFT45 + steps - 1):(RIGHT45 + steps - 1));
}

void driveControl::stop() {
  sendCommand(STOP);
}


void driveControl::setCurrentLocationForTest(int name, int dir) {
  mapGraph->setCurrentNode(mapGraph->getNode(name));
  mapGraph->setCurrentDirection(dir);
}


//Complex Move Commands

void driveControl::forwardToIntersection() {
  move(true);
  pointlineData next = linesensors->getNextIntersection();
  Serial.println(next.toString());
  delay(1000);  //allow pointline sensors to get past the current intersection before polling
  while(linesensors->getData() != next) {
    delay(5);
  }
  stop();
  mapGraph->setCurrentNode(mapGraph->getNextIntersection());
}


//increments of 45 deg, based on intersection sensors
void driveControl::turn45(bool left, int steps) {
  if (steps >= 8 || steps <= 0) {
    return;
  }
  steps = left?(8 - steps):steps;
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
