#include <Wire.h>
#include "driveControl.h"
#include "Graph.h"
#include "intersectionSensors.h"

driveControl::driveControl(Graph * m) {
  Wire.begin();    //only do this if i2c not already started
  mapGraph = m;
  linesensors = new intersectionSensors(mapGraph, L0PIN, L1PIN, l2PIN, R0PIN, R1PIN, R2PIN);
}

void driveControl::sendCommand(int command) {
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

void driveControl::turn(bool left) {
  sendCommand(left?LEFT:RIGHT);
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
  delay(1000);  //allow pointline sensors to get past the current intersection before polling
  while(linesensors->getData() != next) {
    delay(5);
  }
  stop();
  mapGraph->setCurrentNode(mapGraph->getNextIntersection());
}



//TODO
//these turn functions are going to be replaced because of the orientation of the bot, it doesnt allow us to rotate around the token
//so we need to add a hardcoded encoder function to Drive Mega that will move forward slightly and then rotate 45

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
  turn(left);

  while(linesensors->getData() != next) {
    delay(5);
  }
  stop();

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
