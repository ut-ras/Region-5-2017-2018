#include "stepper.h"

// incomplete

// using a 200-step motor
#define MOTOR_STEPS 200
#define steps_per_hole 25

//servo inputs go from 10 - 180 , running below 10 results in constant slow rotation
stepper::stepper(int _stepperPin, int _directionPin){
	stepperPos = 0;

	stepperMotor = stepperMotor::A4988(MOTOR_STEPS, _directionPin, _stepperPin);
	stepperMotor.begin(1, 1);
}

void rotateDisk(uint8_t holeOffset, Direction rotationDirection){
	
	int steps_to_target = holeOffset * steps_per_hole;

    stepper.rotate(steps_to_target);

}
