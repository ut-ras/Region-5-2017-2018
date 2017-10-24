class pointline {
public:
  pointline(int _sensorPin);

  bool getValue();

private:
  int sensorPin;    // select the input pin for the Line sensor

};
