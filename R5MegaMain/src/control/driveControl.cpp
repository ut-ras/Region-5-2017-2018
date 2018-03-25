#include <Wire.h>
#include "driveControl.h"
#include "Graph.h"
#include "intersectionSensors.h"

driveControl::driveControl(Graph * m) {
  Wire.begin();    //only do this if i2c not already started
  map = m;
  linesensors = new intersectionSensors(map, L0PIN, L1PIN, l2PIN, R0PIN, R1PIN, R2PIN);
}

void driveControl::sendCommand(int command) {
  Wire.beginTransmission(DRIVE_MEGA_I2C);
  Wire.write(command);
  Wire.endTransmission();
}

void driveControl::move(bool fwd) {
  if (fwd) {
    sendCommand(FWD1 + speed - 1);
  }
  else {
    sendCommand(BACK1 + speed - 1);
  }
}

void driveControl::turn(bool left) {
  sendCommand(left?LEFT:RIGHT);
}

void driveControl::stop() {
  sendCommand(STOP);
}

//TODO change this to interrupt based movement if we want to use token control at same time
void driveControl::forwardToIntersection() {
  move(true);
  pointlineData next = linesensors->getNextIntersection();
  while(linesensors->getData() != next) {
    delay(5);
  }
  stop();
  map->setCurrentNode(map->getNextIntersection());
}

//increments of 45 deg, based on intersection sensors
void driveControl::turn45(bool left, int steps) {
  if (steps >= 8 || steps <= 0) {
    return;
  }
  
  steps = left?(8 - steps):steps;
  pointlineData next = linesensors->getTurn45Intersection(steps);
  turn(left);
  while(linesensors->getData() != next) {
    delay(5);
  }
  stop();
  
  int nextDir = (map->getCurrentDirection() + steps) % 8;
  map->setCurrentDirection(nextDir);
}

void driveControl::turnTo(int dir) {
  if (dir >= 8 || dir <= 0) {
    return;
  }

  pointlineData next = linesensors->getTurnToIntersection(dir);

  bool left = true;
  int diff = map->getCurrentDirection() - dir;
  if (diff >= 4 || ((diff < 0) && (diff >= -4))) {
    left = false;
  }
  turn(left);

  while(linesensors->getData() != next) {
    delay(5);
  }
  stop();

  map->setCurrentDirection(dir);
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

