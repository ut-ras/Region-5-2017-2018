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
>move this code from "src/pointline/pointline/pointline.ino" to "src/pointline.cpp" (there is an empty file there)
>move the variable sensorPin to a private variable in inc/pointline.h
>in inc/pointline.h change the function from isLine to getValue, to match what is here
*/
