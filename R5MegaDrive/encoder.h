#ifndef ENCODER_H
#define ENCODER_H

//required libraries:
//Digital Write Fast

class encoder {

public:
  encoder(int pa, int pb);
  int getPos();
  int updatePos();

private:
  int pinA, pinB;
  int pos;

};

#endif
