#include "../inc/magnet.h"

magnet::magnet(int _magnetPin){
	pinMode(_magnetPin, OUTPUT);
}

void magnet::magnetOn(){
	digitalWrite(_magnetPin, HIGH);
}

void magnet::magnetOff(){
	digitalWrite(_magnetPin, LOW);
}