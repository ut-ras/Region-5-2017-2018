
#include <Arduino.h>
#include "encoder.h"

encoder::encoder(int pa, int pb) {
  pinA = pa;
  pinB = pb;
  pos = 0;
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
}

int encoder::getPos() {
  return pos;
}

int encoder::updatePos() {
  switch(digitalRead(pinA)){
    case 0:
      if(digitalRead(pinB))pos++;
      else pos--;
      break;
    case 1:
      if(digitalRead(pinB))pos--;
      else pos++;
      break;
  }
  
  //if(digitalRead(pinB)) pos-=2;
  //else pos+=2;
}
