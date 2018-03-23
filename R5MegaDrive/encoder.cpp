
#include "encoder.h"

encoder::encoder() {
  pinModeFast(pinA, INPUT);
  pinModeFast(pinB, INPUT);
  attatchInterrupt(digitalPinToINterrupt(pinA), updatePos, CHANGE);
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
