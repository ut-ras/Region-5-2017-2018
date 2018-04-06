#include "rgbsensor.h"

rgbsensor::rgbsensor() {
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_60X);
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
  Color color = grey;

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

  if((Red > 4600 && Red < 4950) && (Blue > 3350 && Blue < 3650) && (Green > 3800 && Green < 4100)){
    color = red;
  }
  else if ((Red > 4780 && Red  < 4980) && (Blue > 3950 && Blue < 4150) && (Green > 4950 && Green < 5150)){
    color = green;
  }
  else if((Red > 4030 && Red < 4230) && (Blue > 4000  && Blue < 4300) && (Green > 4250 && Green < 4400)){
    color = blue;
  }
  else if((Red > 6000) && (Blue > 4450) && (Green > 5500)){
    color = yellow;
  }
  else if((Red > 4500 && Red  < 4750) && (Blue > 3700 && Blue < 4000) && (Green > 4050 && Green  < 4300)){
    color = magenta;
  }
  else if((Red > 4300 && Red < 4600) && (Blue >  4600 && Blue < 5000) && (Green > 5000 && Green < 5300)){
    color = cyan;
  }
  else if((Red > 3900 && Red < 4200) && (Blue > 3500 && Blue < 3800) && (Green > 4000 && Green <  4300)){
    color = grey;
  }

  Serial.print("\tR:\t"); Serial.print(Red);
  Serial.print("\tG:\t"); Serial.print(Green);
  Serial.print("\tB:\t"); Serial.println(Blue);
  Serial.println(color);
  return color;
}
