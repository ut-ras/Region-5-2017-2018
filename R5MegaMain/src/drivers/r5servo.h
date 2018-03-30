//
// Created by Amr on 15/11/2017.
//

#ifndef r5servo_h
#define r5servo_h

#include <Servo.h>

class r5servo {
public:
    /* Moves the pulley a given distance in the given
     * direction, where true is up and false is down.
     */
    void movePulley(int degrees);

    //initialize the servo
    void init(int _servoPin);
    //constructor
    r5servo();
private:
  Servo thisServo;
  int servoPos;
};

#endif
