#ifdef POINTLINE_H
#define POINTLINE_H

class Pointline {
public:
	// Sets pin value
  Pointline(int _sensorPin);

  // True is black, False is white		
  bool getValue();

private:
  int QRE1113_Pin;    // select the input pin for the Line sensor

};

#endif 
