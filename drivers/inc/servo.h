//
// Created by Amr on 15/11/2017.
//

#ifndef servo_h
#define servo_h

#include <servo.h>

class servo {
public:
    /* Moves the pulley a given distance in the given
     * direction, where true is up and false is down.
     */
    void movePulley(double distance, bool direction);
};

#endif