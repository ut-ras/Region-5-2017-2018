/*
Code to use a single point line sensor
 
 */
#define BLACK 2700
#define WHITE 1000
class pointline{
  int sensorPin = 0;    // select the input pin for the Line sensor

pointline(int _sensorPin) {
  //Set Line Sensor Pin Value 
  sensorPin = _sensorPin;
}

boolean getValue()
{
  
  return sensorPin!=0 && analogRead(sensorPin)>BLACK;
  
}
};
