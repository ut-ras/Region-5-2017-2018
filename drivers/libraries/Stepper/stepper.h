#include <stdint.h>
class stepper {
public:

    stepper(int pin);

    //Direction for rotation
    typedef enum {CLOCKWISE, COUNTERCLOCKWISE} Direction;

    //Rotate stepper motor based on a radian degree input
    void rotateDisk(uint8_t holeOffset, Direction rotationDirection);

};
