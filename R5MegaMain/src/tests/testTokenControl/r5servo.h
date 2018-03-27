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
    void movePulley(double degrees);

    /*Constructor to initialize the servo*/
    r5servo(int _servoPin);
private:
	Servo thisServo;
	int servoPos;
};

#endif
