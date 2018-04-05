#include "rgbsensor.h"

rgbsensor::rgbsensor() {
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  boolean error = false;
  if (!tcs.begin()) {
    error = true;
  }
}

Color rgbsensor::getColor(){
  uint16_t clear, red, green, blue, colours[7] = {0}  ;
  /*RunningMedian rSamples = RunningMedian(5);
  RunningMedian gSamples = RunningMedian(5);
  RunningMedian bSamples = RunningMedian(5);*/
  for(int i = 0; i < 5; i ++){
   
    colours[getColorHelper()]++;
    /* delay(60);  // takes 50ms to read
    tcs.getRawData(&red, &green, &blue, &clear);
    rSamples.add(red);
    gSamples.add(green);
    bSamples.add(blue);*/
  }

  int max = colours[0], maxI = 0;
  for(int i = 1; i <  7; i ++){
    if(colours[i] > max){
      max = colours[i];
      maxI = i;
    }
  }
  return maxI;
  //return getClosestColor(rSamples.getMedian(), gSamples.getMedian(), bSamples.getMedian());
}

Color rgbsensor::colorTester(){
  uint16_t clear, red, green, blue;
  RunningMedian rSamples = RunningMedian(100);
  RunningMedian gSamples = RunningMedian(100);
  RunningMedian bSamples = RunningMedian(100);
  delay(1000);
  //tcs.setInterrupt(false);
  for(int i = 0; i < 100; i ++){
    delay(60);  // takes 50ms to read
    tcs.getRawData(&red, &green, &blue, &clear);
    rSamples.add(red);
    gSamples.add(green);
    bSamples.add(blue);
  }

  Serial.print("Red: "); Serial.println(rSamples.getMedian());
  Serial.print("Green: "); Serial.println(gSamples.getMedian());
  Serial.print("Blue: "); Serial.println(bSamples.getMedian());
  return 0;
}

Color rgbsensor::getColorHelper(){
  uint16_t clear, red, green, blue;
  //tcs.setInterrupt(false);
  delay(60);  // takes 50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);
  //tcs.setInterrupt(true);  // turn on LED
  return getClosestColor(red,green,blue);
}
Color rgbsensor::getClosestColor(int Red,int Green, int Blue)
{
  // int redThreshold = 100;
  // int blueThreshold = 80;
  // int yellowThreshold = 100;
  // int greyThreshold = 25;
  // int cyanThreshold = 250;
  // int greenThreshold = 150;
  // int purpleThreshold = 50;
  Color color = unknown;

  /*if((((Red - Blue) > redThreshold) && ((Red - Green) > redThreshold)))
  {
    color = red;
  }
  else if(((abs(Red - Blue) < purpleThreshold) && ((Blue - Green) > purpleThreshold)))
  {
    color = magenta;
  }
  else if((((Blue - Red) > blueThreshold) && ((Blue - Green) > blueThreshold)))
  {
    color = blue;
  }
  else if((((Green - Red) > cyanThreshold) && ((Blue - Green) < cyanThreshold)))
  {
    color = cyan;
  }
  else if((((Green - Red) > greenThreshold) && ((Green - Blue) > greenThreshold)))
  {
    color = green;
  }
  else if((((Green - Red) < yellowThreshold) && ((Green - Blue) > yellowThreshold)))
  {
    color = yellow;
  }
  else if(((abs(Red - Blue) < greyThreshold) && (abs(Red - Green) < greyThreshold)))
  {
    color = grey;
  }*/

  if((Red > 260 && Red < 280) && (Blue > 240 && Blue < 260) && (Green > 270 && Green < 290)){
    color = red;
  }
  else if ((Red > 265 && Red  < 285) && (Blue > 250 && Blue < 270) && (Green > 300 && Green < 320)){
    color = green;
  }
  else if((Red > 245 && Red < 265) && (Blue > 255 && Blue < 275) && (Green > 280 && Green < 300)){
    color = blue;
  }
  else if((Red > 300 && Red < 340) && (Blue > 255 && Blue < 295) && (Green > 315 && Green < 355)){
    color = yellow;
  }
  else if((Red > 250 && Red  < 290) && (Blue > 240 && Blue < 280) && (Green > 270 && Green  < 310)){
    color = magenta;
  }
  else if((Red > 240 && Red < 280) && (Blue >  260 && Blue < 300) && (Green > 290 && Green < 330)){
    color = cyan;
  }
  else if((Red > 240 && Red < 280) && (Blue > 235 && Blue < 275) && (Green > 270 && Green <  310)){
    color = grey;
  }

  Serial.print("\tR:\t"); Serial.print(Red);
  Serial.print("\tG:\t"); Serial.print(Green);
  Serial.print("\tB:\t"); Serial.println(Blue);
  Serial.println(color);
  return color;
}
