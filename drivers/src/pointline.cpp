#include "../inc/pointline.h"


/*
Code to use a single point line sensor

 */

#define BLACK 2700
#define WHITE 1000

pointline::pointline(int _sensorPin) {
  //Set Line Sensor Pin Value
  sensorPin = _sensorPin;
  
  pinMode(sensorPin, INPUT);
}

boolean pointline::getValue() {
  return sensorPin!=0 && analogRead(sensorPin)>BLACK;
}
