
#include <Arduino.h>
#include "encoder.h"
#include "digitalWriteFast.h"

encoder::encoder(int pa, int pb) {
  pinA = pa;
  pinB = pb;
  pos = 0;
  pinModeFast(pinA, INPUT);
  pinModeFast(pinB, INPUT);
}

int encoder::getPos() {
  return pos;
}

int encoder::updatePos() {
  switch(digitalReadFast(pinA)){
  case 0:
    if(digitalReadFast(pinB)) pos++;
    else pos--;
    break;
  case 1:
    if(digitalReadFast(pinB)) pos--;
    else pos++;
    break;
    }
}
