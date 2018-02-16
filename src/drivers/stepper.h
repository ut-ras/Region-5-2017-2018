#include <stdint.h>
#include "A4988.h"

class stepper {
public:

    stepper(int _stepperPin, int _directionPin);

    //Direction for rotation
    typedef enum {CLOCKWISE, COUNTERCLOCKWISE} Direction;

    //Rotate stepper motor based on a radian degree input
    void rotateDisk(uint8_t holeOffset, Direction rotationDirection);

private:
	int stepperPos;
	A4988 stepperMotor;
};
