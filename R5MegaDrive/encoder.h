#ifndef ENCODER_H
#define ENCODER_H

class encoder {

public:
  encoder(int pa, int pb);
  int getPos();


private:
  int updatePos();

  int pinA, pinB;
  int pos;

}

#endif
