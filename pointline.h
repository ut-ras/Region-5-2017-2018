#include "Arduino.h"

class pointline {
public:
	// Sets pin value
  pointline(int _sensorPin);

  // True is black, False is white		
  bool getValue();

private:
  int QRE1113_Pin;    // select the input pin for the Line sensor

};
