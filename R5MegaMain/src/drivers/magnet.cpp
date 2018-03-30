#include "magnet.h"
#include <Arduino.h>

magnet::magnet(int _magnetPin){
  magPin = _magnetPin;
	pinMode(_magnetPin, OUTPUT);
}

void magnet::magnetOn(){
	digitalWrite(magPin, HIGH);
}

void magnet::magnetOff(){
	digitalWrite(magPin, LOW);
}
