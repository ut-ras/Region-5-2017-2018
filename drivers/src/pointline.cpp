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


/*
notes from cole 10\18\17
this looks good, almost done! just need to tie this back into our code structure
todo:
>don't define the class within pointline.cpp - the class declaration should be in pointline.h
>when implementing a member function outside of a class, declare methods like this - pointline::pointline(int _sensorPin)
>move the variable sensorPin to a private variable in inc/pointline.h
>in inc/pointline.h change isLine to getValue, match what is here
>#include for pointline.h
*/
