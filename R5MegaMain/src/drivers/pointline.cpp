#include "pointline.h"


/*
Code to use a single point line sensor

 */

pointline::pointline(int _sensorPin) {
  //Set Line Sensor Pin Value
  QRE1113_Pin = _sensorPin;
}

bool pointline::getValue() {
//Returns value from the QRE1113
//Lower numbers mean more refleacive
//More than 3000 means nothing was reflected.
pinMode( QRE1113_Pin, OUTPUT );
digitalWrite( QRE1113_Pin, HIGH );
delayMicroseconds(10);
pinMode( QRE1113_Pin, INPUT );

long time = micros();

//time how long the input is HIGH, but quit after 3ms as nothing happens after that
while (digitalRead(QRE1113_Pin) == HIGH && micros() - time < 3000);
int diff = micros() - time;
Serial.println(diff);
return (diff >= 175 && diff < 300 || diff > 650);
}
