#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H

#include "Graph.h"
#include "intersectionSensors.h"

#define DRIVE_MEGA_I2C 8

//intersection sensor pins
#define L0PIN 22
#define L1PIN 23
#define l2PIN 24
#define R0PIN 25
#define R1PIN 26
#define R2PIN 27

enum Commands{FWD1, FWD2, FWD3, BACK1, BACK2, BACK3, LEFT, RIGHT, STOP};

class driveControl {

public:
  driveControl(Graph * m);

  void move(bool fwd);
  void turn(bool left);
  void stop();

  void forwardToIntersection();
  void turn45(bool left, int steps); //increments of 45 deg
  void turnTo(int dir);

  //0, 1, or 2
  void setSpeed(int s);
  int getSpeed();

  intersectionSensors * getIntersectionSensors();

private:
  void sendCommand(int command);

  Graph * map;
  intersectionSensors * linesensors;
  int speed; //1, 2, or 3
};

#endif
