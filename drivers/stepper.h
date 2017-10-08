#include <stdint.h>
class stepper {
    //Direction for rotation
    typedef enum {CLOCKWISE, COUNTERCLOCKWISE} Direction;
    
    //Rotate stepper motor based on a radian degree input
    void rotateStepperAngle(double angleInRadians, Direction rotationDirection);

    //Rotate stepper motor based on a step value
    void rotateStepperSteps(int stepValue, Direction rotationDirection);


}
