#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H

#include "Graph.h"
#include "intersectionSensors.h"

#define DRIVE_MEGA_I2C 8

//intersection sensor pins
#define R0PIN 38
#define R1PIN 34
#define R2PIN 30
#define L0PIN 40
#define L1PIN 44
#define L2PIN 46

enum Commands{BLANK, FWD1, FWD2, FWD3, BACK1, BACK2, BACK3, LEFTIP, RIGHTIP, FWDNOLINE,  BACKNOLINE, LEFT45, LEFT90, LEFT135, LEFT180, RIGHT45, RIGHT90, RIGHT135, RIGHT180, STOP, RETURNWHITELEFT, RETURNWHITERIGHT};    //from i2c

class driveControl {

public:
  driveControl(Graph * m);

  void forwardAtStart();

  void move(bool fwd);
  void turnManeuver(bool left, int steps);
  void stop();

  void forwardToIntersection();
  void turn45(bool left, int steps); //increments of 45 deg
  void turnTo(int dir);

  //1, 2, 3
  void setSpeed(int s);
  int getSpeed();

  intersectionSensors * getIntersectionSensors();

  void testSendCommand();
  void sendCommand(uint8_t command);

private:

  Graph * mapGraph;
  intersectionSensors * linesensors;
  int speed; //1, 2, or 3
};

#endif
