#include "tokenControl.h"
tokenControl t;
void setup() {
  Serial.begin(9600); 
  delay(1000);
  t.initialize();
  delay(1000);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  t.pickUpToken();
  while(1);
}
