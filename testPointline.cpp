#include "pointline.h"      //quotations bc relative pathing

pointline* point;             // * because pointer. without the start it would try to create a new pointline.





void setupPointLineTest(int pin){

  point = new pointline(pin);       // new becuase it's a pointer so we're allocating the memory dynamically. without hte new then it would be static.


}

void loopPointLineTest(){
  Serial.println(point->getValue());

}

