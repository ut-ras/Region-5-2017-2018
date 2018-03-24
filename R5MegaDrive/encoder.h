#ifndef ENCODER_H
#define ENCODER_H

#include <digitalWriteFast.h>

class encoder {

public:
  encoder(int pa, int pb);  //pinA MUST be interrupt capable
  int getPos();


private:
  int updatePos();

  int pinA, pinB;
  int pos;

};

#endif
