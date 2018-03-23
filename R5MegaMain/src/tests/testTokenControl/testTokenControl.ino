#include "tokenControl.cpp"
#include "servo.cpp"
#include "stepper.cpp"
#include "magnet.cpp"

void setup() {
  tokenControl t;
  delay(1000);
}

void loop() {
  t.pickUpToken();

  while(1);
}
