#include "rgbsensor.h"

rgbsensor::rgbsensor() {
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  boolean error = false;
  if (!tcs.begin()) {
    error = true;
  }
}

Color rgbsensor::getColor(){
  uint16_t clear, red, green, blue, colours[7];
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

  int max = 0, maxI = 0;

  for(int i = 0; i <  7; i ++){
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

  if((Red > 330 && Red < 370) && (Blue > 280 && Blue < 320) && (Green > 330 && Green < 370)){
    color = red;
  }
  else if ((Red > 330 && Red  < 370) && (Blue > 300 && Blue < 340) && (Green > 350 && Green < 390)){
    color = green;
  }
  else if((Red > 290 && Red < 320) && (Blue > 310 && Blue < 330) && (Green > 335 && Green < 360)){
    color = blue;
  }
  else if((Red > 390 && Red < 430) && (Blue > 310 && Blue < 350) && (Green > 390 && Green < 430)){
    color = yellow;
  }
  else if((Red > 300 && Red  < 330) && (Blue > 270 && Blue < 310) && (Green > 300 && Green  < 340)){
    color = magenta;
  }
  else if((Red > 310 && Red < 350) && (Blue >  310 && Blue < 350) && (Green > 360 && Green < 400)){
    color = cyan;
  }
  else if((Red > 290 && Red < 330) && (Blue > 270 && Blue < 310) && (Green > 320 && Green <  360)){
    color = grey;
  }

    Serial.print("\tR:\t"); Serial.print(Red);
    Serial.print("\tG:\t"); Serial.print(Green);
    Serial.print("\tB:\t"); Serial.println(Blue);
    Serial.println(color);
  return color;
}
