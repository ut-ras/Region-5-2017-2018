#define DUTY_CYCLE 0.2
// lower bound = 50us
// reasonable upper bound = 5000us
#define PERIOD 300
// using a 200-step motor
#define MOTOR_STEPS 6400
#define HOLES 800

#include "stepper.h"

// Initializer
stepper::stepper(int _stepperPin, int _directionPin)
{
  stepperPos = 0;

  stepperPin = _stepperPin;
  directionPin = _directionPin;

  pinMode(stepperPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
}

// Rotate disk by angle in Direction
void stepper::rotateDisk(float angle, stepper::Direction rotationDirection)
{
  digitalWrite(directionPin, rotationDirection);

    for(int i=0; i<(angle * 160 / 9); i++)
    {
      digitalWrite(stepperPin, HIGH);
      delayMicroseconds(PERIOD * DUTY_CYCLE);
      digitalWrite(stepperPin, LOW);
      delayMicroseconds(PERIOD * (1-DUTY_CYCLE));
    }
}
