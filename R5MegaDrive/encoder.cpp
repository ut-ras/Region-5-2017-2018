
#include <Arduino.h>
#include "encoder.h"
//#include digital write fast

encoder::encoder(int pa, int pb) {
  pinModeFast(pinA, INPUT);
  pinModeFast(pinB, INPUT);
  attatchInterrupt(digitalPinToInterrupt(pinA), updatePos, CHANGE);
}

int encoder::getPos() {
  return pos;
}

int encoder::updatePos() {
  switch(digitalReadFast(pinA)){
  case 0:
    if(digitalReadFast(pinB))pos++;
    else pos--;
    break;
  case 1:
    if(digitalReadFast(pinB))pos--;
    else pos++;
    break;
    }
}
