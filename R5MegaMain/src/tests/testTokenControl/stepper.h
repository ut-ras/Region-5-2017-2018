#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>
#include "arduino.h"

class stepper {
public:

    stepper(int _stepperPin, int _directionPin);

    //Direction for rotation
    typedef enum {CLOCKWISE, COUNTERCLOCKWISE} Direction;

    //Rotate stepper motor based on a radian degree input
    void rotateDisk(float angle, Direction rotationDirection);

private:
	int stepperPos;
	int stepperPin;
	int directionPin;
};

#endif
