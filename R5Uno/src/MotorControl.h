#ifndef MOTORCONTROL_H

class MotorControl {

public:
  MotorControl();
  void move(bool fwd);
  void turn(bool left);
  void stop();

private:
  void setSpeed(int s);
  void calculateVelocity();

  //variable to hold Motor
  //variable to hold PID
  int time;

}
