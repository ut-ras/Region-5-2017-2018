
#include <Arduino.h>
#include "encoder.h"
#include "digitalWriteFast.h"

encoder::encoder(int pa, int pb) {
  pinA = pa;
  pinB = pb;
  pos = 0;

}

int encoder::getPos() {
  return pos;
}

int encoder::updatePos() {
  if(digitalReadFast(pinB)) {
    pos--;
  }
  else {pos++;}
    
}
