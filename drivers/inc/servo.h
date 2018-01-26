//
// Created by Amr on 15/11/2017.
//

#ifndef servo_h
#define servo_h

#include <Servo.h>

class servo {
public:
    /* Moves the pulley a given distance in the given
     * direction, where true is up and false is down.
     */
    void movePulley(double distance, bool direction);

    /*Constructor to initialize the servo*/
    servo();
private:
	Servo thisServo;
	int servoPos;
};

#endif