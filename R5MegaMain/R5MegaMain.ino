#include <Time.h>
#include <Arduino.h>

#include "src/control/tokenControl.h"
#include "src/control/driveControl.h"
#include "src/control/Graph.h"

#define MAIN_MEGA_I2C 0x10

/* Required libraries (sketch/include library/manage libraries to add)
 * Adafruit_TCS34725
 */

#define FWD true

//TODO: Change the button pin numbers to the appropriate pins
//const int startButton = 2;
//const int stopButton = 3;

tokenControl *tokenController;
driveControl *driveController;
Graph * mapGraph;

/* void waitForStart() {
  //While not pressed
  while(digitalRead(startButton) == 1){
    delay(100);
  }
  //send i2c to main
}

void stopISR(){
  while(true);
}*/

void setup() {
  // put your setup code here, to run once:]
  Serial.begin(9600);

  //Negative Logic Buttons
  //pinMode(startButton, INPUT_PULLUP);
  //pinMode(stopButton, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(stopButton), stopISR, FALLING);
  
  mapGraph = new Graph();
  tokenController = new tokenControl(mapGraph);
  driveController = new driveControl(mapGraph);

  driveController->sendCommand(STOP);
    
  Wire.begin();

  //waitForStart();

  //mapGraph->printSerial();

  delay(2000);
  //testTokenControl();
  //printIntersectionData();
  //testDriveControl();
  //testGUI();
  //testCombo();
  testSimple();

}

void loop() {
  // put your main code here, to run repeatedly:
  Blink();
  round1();
}

//debugging gui
/*void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    int8_t inChar = Serial.parseInt();
    if ((inChar >= 0) && (inChar <= STOP)) {
      driveController->sendCommand(inChar);
    }
  }
}*/

void testCombo() {
  Blink();
  driveController->sendCommand(STOP);
  while(1){
    for(int i = 0; i < 2; i ++){
      driveController->sendCommand(STOP);
      tokenController->pickUpToken();
      driveController->forwardToIntersection();
    }
    tokenController->pickUpToken();
    driveController->turnManeuver(true, 2);
  }
}

void testTokenControl() {
  Blink();
  //tokenController->goToEveryColour();
  //tokenController->depositTokens(magenta);
    Serial.println("Start");
    //tokenController->readColour();
    //tokenController->pickUpToken(); 
    //Serial.println("----");
    //Serial.println("");
    delay(2000);
    while(1){
    //tokenController->readColour();
    //tokenController->pickUpToken(); 
    tokenController->pickUpToken(); 
    Serial.println("----");
    Serial.println("");
    delay(5000);
    }
}
      
void Blink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void testDriveControl() {
  //driveController->move(true);

  driveController->setSpeed(2);
  
  setCurrentLocationForTest(R5, 4);  
  Serial.println(mapGraph->getCurrentNode()->toString());
  driveController->forwardToIntersection();
  tokenController->pickUpToken();
  driveController->setSpeed(2);
  Serial.println(mapGraph->getCurrentNode()->toString());
  delay(3000);
  driveController->forwardToIntersection();
  tokenController->pickUpToken();
  driveController->setSpeed(2);
  Serial.println(mapGraph->getCurrentNode()->toString());
  delay(3000);
  driveController->turn45(true, 2);
  driveController->forwardToIntersection();
  tokenController->pickUpToken();
  driveController->setSpeed(2);
  
}

//where the bot is starting, (location, dir)
void setCurrentLocationForTest(int name, int dir) {
  mapGraph->setCurrentNode(mapGraph->getNode(name));
  mapGraph->setCurrentDirection(dir);
  Serial.println("set node to " + String(mapGraph->getNode(name)->toString())+ " set direction to " + String(mapGraph->getCurrentDirection()));
}

void printIntersectionData() {
  intersectionSensors * s = driveController->getIntersectionSensors();
  while(1) {
    Serial.println(s->getData().toString());
    delay(500);
  }
}

/*
 * Coded by Catherine, Colton
 * Commented code with "//" - is asumming we do not need
 *                            but might need in the future
 * CHECK delay(1000) - is this the correct parameters?
 *                     delay is there for the robot to move
 *                       inside the colored box
 */

//Useful Function Prototypes:
void dropOffTokens(int color, int level);
void red2cyan(bool collectTokens);
void red2green(bool collectTokens);
void green2red(bool collectTokens);
void green2blue(bool collectTokens);
void blue2green(bool collectTokens);
void blue2yellow(bool collectTokens);
void yellow2blue(bool collectTokens);
void yellow2magenta(bool collectTokens);
void magenta2yellow(bool collectTokens);
void magenta2cyan(bool collectTokens);
void cyan2magenta(bool collectTokens);
void cyan2red(bool collectTokens);
void color2grey(int colorStart, bool collectTokens);
void grey2color(int colorEnd, bool collectTokens);
void goColor2Color(int colorStart, int colorEnd, bool tokenCollect);
void changeLevel(int color, int startLevel, int endLevel);


void testGUI(){
  setCurrentLocationForTest(Y4, 2);
  driveController->turnTo(0);
  driveController->forwardToIntersection(); //magenta;
  driveController->forwardToIntersection(); //cyan;
  driveController->turnTo(6);
  driveController->forwardToIntersection(); //red;
  goColor2Color(red, blue, true);
  changeLevel(blue, 4, 2);
  goColor2Color(blue, cyan, true);

}


void testSimple() {

  driveController->forwardAtStart();  
  Serial.println("hit the white box edge");
  driveController->forwardAtStart();
  Serial.println("hit the first square line");
  driveController->forwardAtStart();
  Serial.println("hit the second square line");
  driveController->forwardAtStart();  
  Serial.println("hit the third square line");
  driveController->forwardAtStart();
  Serial.println("hit the fourth box line");
  driveController->turn45(true, 2);
  Serial.println("turn to the left (toward blue)");

  setCurrentLocationForTest(Y4, 6);
  Serial.println(mapGraph->getCurrentNode()->toString());
  driveController->forwardToIntersection();
  Serial.println("drive to Blue 4");
  tokenController->pickUpToken();
  Serial.println("pick up the token");
  driveController->turn45(true, 1);
  Serial.println("turn towards blue box");
  //setCurrentLocationForTest(Bl4, 5);  //redundant
  driveController->forwardToIntersection();
  Serial.println("drive to Blue 3");
  driveController->forwardToIntersection();   //drive to Bl2
  Serial.println("drive to Blue 2");
  tokenController->pickUpToken();
  Serial.println("pick up the token");
  dropOffTokens(blue, 2);
  Serial.println("drop off in blue");
}

void allIn() {
  bool checked[] = {false, false, false, false, false, false, false};

  driveController->forwardAtStart();  
  Serial.println("hit the white box edge");
  driveController->forwardAtStart();
  Serial.println("hit the first square line");

  setCurrentLocationForTest(bl1, 2);
  goColor2Color(blue, yellow, true);
  if(mapGraph->getNumTokens(yellow) > 0) {
    dropOffTokens(yellow, 1);
    checked[yellow] = true;
  }

  goColor2Color(yellow, red, true);
  if(mapGraph->getNumTokens(red) > 0) {
    dropOffTokens(red, 1);
    checked[red] = true;
  }

  goColor2Color(red, cyan, true);
  if(mapGraph->getNumTokens(cyan) > 0) {
    dropOffTokens(cyan, 1);
    checked[cyan] = true;
  }

  goColor2Color(cyan, blue, true);
  if(mapGraph->getNumTokens(blue) > 0) {
    dropOffTokens(blue, 1);
    checked[blue] = true;
  }

  goColor2Color(blue, green, true);
  if(mapGraph->getNumTokens(green) > 0) {
    dropOffTokens(green, 1);
    checked[green] = true;
  }

  goColor2Color(green, grey, true);
  if(mapGraph->getNumTokens(grey) > 0) {
    dropOffTokens(grey);
    checked[grey] = true;
  } 

  goColor2Color(grey, magenta, true);
  if(mapGraph->getNumTokens(magenta) > 0) {
    dropOffTokens(magenta);
    checked[magenta] = true;
  }


  //Wrap up any we missed colors
  if(!checked[yellow]){
    goColor2Color(currentColor, yellow, false);
    dropOffTokens(yellow, 1);
    currentColor = yellow;
  }

  if(!checked[blue]){
    goColor2Color(currentColor, blue, false);
    dropOffTokens(blue, 1);
    currentColor = blue;
  }

  if(!checked[red]){
    goColor2Color(currentColor, red, false);
    dropOffTokens(red, 1);
    currentColor = red;
  }

  if(!checked[cyan]){
    goColor2Color(currentColor, cyan, false);
    dropOffTokens(cyan, 1);
    currentColor = cyan;
  }

  if(currentColor == green) {
    goColor2Color(green, blue, 1);
    currentColor = blue;
  }

  if(currentColor == magenta){
    goColor2Color(magenta, yellow, 1);
    currentColor = yellow;
  }

  if( (currentColor == red) || (currentColor == yellow) ){
    sendCommand(???_LEFT);
    wait(???);
  }

  if( (currentColor == blue) || (currentColor == cyan)){
    sendCommand(???_RIGHT);
    wait(???);
  }

  //stop?


}

//Strategies for each round:
void round1() {
  int inventory[7];
  int currentLevel = 0;
 //  time_t startTime = second();
 // time_t endTime = 300 + startTime; //5 minutes
 
  //Start at White Box closest to the yellow
  driveController->forwardAtStart();
  currentLevel = 4;

  ///Go to y4
  driveController->turnTo(2);  //probably replace with turnTo(2);
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  yellow2magenta(true);
  magenta2cyan(true);
  cyan2red(true);
  red2green(true);
  green2blue(true);

  //move to level 2 square
  changeLevel(blue, 4, 2);
  currentLevel = 2;

  //Tour the level 2 square, checking if we should drop off at each color
  if (mapGraph->getNumTokens(blue) == 2) {
    dropOffTokens(blue, currentLevel);
  } 
  blue2green(true);

  if (mapGraph->getNumTokens(green) == 2) {
    dropOffTokens(green, currentLevel);
  }
  green2red(true);
  
  if (mapGraph->getNumTokens(red) == 2) {
    dropOffTokens(red, currentLevel);
  }
  red2cyan(true);
 
  if(mapGraph->getNumTokens(cyan) == 2) {
    dropOffTokens(cyan, currentLevel);
  }
  cyan2magenta(true);

  if(mapGraph->getNumTokens(magenta) == 2) {
    dropOffTokens(magenta, currentLevel);
  }
  magenta2yellow(true);

  if(mapGraph->getNumTokens(yellow) == 2) {
    dropOffTokens(yellow, currentLevel);
  }

  //write code to get into the white box;
}

void round2(){
  int inventory[7];
  int currentLevel = 0;
 //  time_t startTime = second();
 // time_t endTime = 300 + startTime; //5 minutes
 
  //Start at White Box closest to the yellow
  for (int i = 0; i < 5; i++) {
    driveController->forwardToIntersection();
  }
  currentLevel = 4;

  ///Go to y4
  driveController->turnTo(2);  //probably replace with turnTo(2);
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  yellow2magenta(true);
  magenta2cyan(true);
  cyan2red(true);
  red2green(true);
  green2blue(true);

  //move to level 3 square
  changeLevel(blue, 4, 3);
  currentLevel = 3;

  //tour level 3 square
  blue2green(true);
  green2red(true);
  red2cyan(true);
  cyan2magenta(true);
  magenta2yellow(true);

  //move to level 2 square
  changeLevel(blue, 3, 2);
  currentLevel = 2;

  //Tour the level 2 square, checking if we should drop off at each color
  if (mapGraph->getNumTokens(yellow) == 2) {
    dropOffTokens(yellow, currentLevel);
  } 
  yellow2magenta(true);

  if (mapGraph->getNumTokens(magenta) == 2) {
    dropOffTokens(magenta, currentLevel);
  }
  magenta2cyan(true);
  
  if (mapGraph->getNumTokens(cyan) == 2) {
    dropOffTokens(cyan, currentLevel);
  }
  cyan2red(true);
 
  if(mapGraph->getNumTokens(red) == 2) {
    dropOffTokens(red, currentLevel);
  }
  red2green(true);

  if(mapGraph->getNumTokens(green) == 2) {
    dropOffTokens(green, currentLevel);
  }
  green2blue(true);

  if(mapGraph->getNumTokens(blue) == 2) {
    dropOffTokens(blue, currentLevel);
  }

  //write code to get into the white box at the end;
}

//Drop off tokens in the corner boxes (doesn't handle grey right now)
void dropOffTokens(int color, int level) {

  int boxDir[] = {7, 6, 5, 3, 2, 1};  //direction of each box relative to its node, indexed by color enum
  
  int dir2Box = boxDir[color];
  driveController->turnTo(dir2Box);

  for(int i=0; i<level; i++)
    driveController->forwardToIntersection(); //take the diagonal path until you reach the box

  driveController->sendCommand(FWDNOLINE);
  delay(1000);
  driveController->stop();
  tokenController->depositAllTokens(color);
  
  //return to the node we came from
  int dir2Node = dir2Box - 4;                         
  dir2Node = (dir2Node < 0)? dir2Node + 8 : dir2Node; //make sure to wrap around to 7 if we go negative
  driveController->turnTo(dir2Node);

  //driveController->forwardToIntersection(); //may require an extra call to get past the box edge
  for(int i=0; i<level; i++)
    driveController->forwardToIntersection();
}

void red2cyan(bool collectTokens) {
    driveController->turnTo(2);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void red2green(bool collectTokens) {
  driveController->turnTo(4);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void green2red(bool collectTokens) {
  driveController->turnTo(0);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void green2blue(bool collectTokens) {
  driveController->turnTo(4);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void blue2green(bool collectTokens) {
  driveController->turnTo(0);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void blue2yellow(bool collectTokens) {
  driveController->turnTo(2);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void yellow2blue(bool collectTokens) {
  driveController->turnTo(6);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void yellow2magenta(bool collectTokens) {
  driveController->turnTo(0);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void magenta2yellow(bool collectTokens) {
  driveController->turnTo(4);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void magenta2cyan(bool collectTokens) {
  driveController->turnTo(0);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void cyan2magenta(bool collectTokens){
  driveController->turnTo(4);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void cyan2red(bool collectTokens) {
  driveController->turnTo(6);
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
}

void color2grey(int colorStart, bool collectTokens) {

  int inwardDirs[] = {3, 2, 1, 7, 6, 5};
  int thisDir = inwardDirs[colorStart];
  driveController->turnTo(thisDir);

  for(int i = 0; i < 4; i++) {
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
  }
}

void grey2color(int colorEnd, bool collectTokens) {

  int outwardDirs[] = {7, 6, 5, 3, 2, 1};
  int thisDir = outwardDirs[colorEnd];
  driveController->turnTo(thisDir);

  for(int i = 0; i < 4; i++) {
    driveController->forwardToIntersection();
    if(collectTokens)
      tokenController->pickUpToken();
  }
}

void goColor2Color(int colorStart, int colorEnd, bool tokenCollect) {

  if(colorStart == red) {
    switch(colorEnd){
      case green:
        red2green(tokenCollect);
        break;
      case blue:
        red2green(tokenCollect);
        green2blue(tokenCollect);
        break;
      case yellow:
        color2grey(red, tokenCollect);
        grey2color(yellow, tokenCollect); 
        break;
      case magenta:
        color2grey(red, tokenCollect);
        grey2color(magenta, tokenCollect);
        break;
      case cyan:
        red2cyan(tokenCollect);
        break;
    }
  }

  if(colorStart == green) {
    switch(colorEnd){
      case red:
        green2red(tokenCollect);
        break;
      case blue:
        green2blue(tokenCollect);
        break;
      case yellow:
        color2grey(green, tokenCollect);
        grey2color(yellow, tokenCollect); 
        break;
      case magenta:
        color2grey(green, tokenCollect);
        grey2color(magenta, tokenCollect);
        break;
      case cyan:
        color2grey(green, tokenCollect);
        grey2color(cyan, tokenCollect);
        break;
    }
  }

  if(colorStart == blue) {
    switch(colorEnd){
      case red:
        blue2green(tokenCollect);
        green2red(tokenCollect);
        break;
      case green:
        blue2green(tokenCollect);
        break;
      case yellow:
        blue2yellow(tokenCollect); 
        break;
      case magenta:
        color2grey(blue, tokenCollect);
        grey2color(magenta, tokenCollect);
        break;
      case cyan:
        color2grey(blue, tokenCollect);
        grey2color(cyan, tokenCollect);
        break;
    }
  }

  if(colorStart == yellow) {
    switch(colorEnd){
      case red:
        color2grey(yellow, tokenCollect);
        grey2color(red, tokenCollect); 
        break;
      case green:
        color2grey(yellow, tokenCollect);
        grey2color(green, tokenCollect);
        break;
      case blue:
        yellow2blue(tokenCollect); 
        break;
      case magenta:
        yellow2magenta(tokenCollect);
        break;
      case cyan:
        yellow2magenta(tokenCollect);
        magenta2cyan(tokenCollect);
        break;
    }
  }

  if(colorStart == magenta) {
    switch(colorEnd){
      case red:
        color2grey(magenta, tokenCollect);
        grey2color(red, tokenCollect); 
        break;
      case green:
        color2grey(magenta, tokenCollect);
        grey2color(green, tokenCollect);
        break;
      case blue:
        color2grey(magenta, tokenCollect);
        grey2color(blue, tokenCollect);
        break;
      case yellow:
        magenta2yellow(tokenCollect);
        break;
      case cyan:
        magenta2cyan(tokenCollect);
        break;
    }
  }

  if(colorStart == cyan) {
    switch(colorEnd){
      case red:
        cyan2red(tokenCollect); 
        break;
      case green:
        color2grey(cyan, tokenCollect);
        grey2color(green, tokenCollect);
        break;
      case blue:
        color2grey(cyan, tokenCollect);
        grey2color(blue, tokenCollect);
        break;
      case yellow:
        cyan2magenta(tokenCollect);
        magenta2yellow(tokenCollect);
        break;
      case magenta:
        cyan2magenta(tokenCollect);
        break;
    }
  }
}

void changeLevel(int color, int startLevel, int endLevel) {
  
  int inwardDirs[] = {3, 2, 1, 7, 6, 5};
  int outwardDirs[] = {7, 6, 5, 3, 2, 1};

  int dir;
  int levelsChanged;
  if(startLevel > endLevel) {
    dir = outwardDirs[color];
    levelsChanged = startLevel - endLevel;
  } else {
    dir = inwardDirs[color];
    levelsChanged = endLevel - startLevel;
  }

  driveController->turnTo(dir);
  for(int i = 0; i < levelsChanged; i++)
    driveController->forwardToIntersection();

} 



/*
void round3() {
	int inventory[6];
  time_t startTime = second();
  time_t endTime = 480 + startTime; //time for 8 seconds


  //Start at yellow box
  //assuming it is align with the y1 box:
  driveController->forwardToIntersection();
 /// driv6eController->turn45();
  driveController->forwardToIntersection();

  //collect across diagonal going from yellow to red
	for(int i = 0; i < 4; i++){
		driveController->forwardToIntersection();
		tokenController->pickUpToken();
    //assuming Map is updated
	}

  //Cross grey box
	driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //Continue to r1
	for(int i = 0; i < 4; i++){
		driveController->forwardToIntersection();
		tokenController->pickUpToken();
	}

  //At Red box, check if should drop off RED tokens
  if(mapGraph->getNumTokens(red) == 2){
    ///driveController->turn45(true, 4);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(red);
    driveController->turn45(true, 4);
    driveController->forwardToIntersection();
    driveController->turn45(false, 1);
  } else {
    //Can't drop off tokens
    //Turn robot to align with g1
    driveController->turn45(true,3);
  }

  //go to g1
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //Check if we can drop off GREEN tokens
  if(mapGraph->getNumTokens(green) == 2){
    //drop off green tokens on way by
    driveController->turn45(false, 2);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(green);
    driveController->turn45(true,4);
    driveController->forwardToIntersection();
  } else {
    driveController->turn45(true,2);
  }

  //go across to m1
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //cross grey box
  driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //continue to m1
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //Check if we can drop off MAGENTA tokens
  if(mapGraph->getNumTokens(magenta) == 2){
    //driveController->turnTo(2);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(magenta);
    driveController->turn45(true,4);
    driveController->forwardToIntersection();
    driveController->turn45(false,2);
  } else {
    driveController->turn45(true,2);
  }

  //go to c1
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //Check if depsoit CYAN tokens
  if( mapGraph->getNumTokens(cyan) == 2){
    //drop off cyan tokens on way by
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(cyan);
    driveController->turn45(true,4);
    driveController->forwardToIntersection();
  } {
    driveController->turn45(true,3);
  }

  //go to b1
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //cross grey box
  driveController->move(FWD);
  delay(1000);
  driveController->stop();

  //continue to blue box
  for(int i = 0; i < 4; i++){
    driveController->forwardToIntersection();
    tokenController->pickUpToken();
  }

  //---------------------------------------------------
  //           DROP OFF PHASE

  //drop off blue tokens
  driveController->forwardToIntersection();
  driveController->move(FWD);
  delay(1000);
  driveController->stop();
  tokenController->depositTokens(blue);

  //get back to b1
  driveController->turn45(true,4);
  driveController->forwardToIntersection();

  //go to g1
  driveController->turn45(true,1);
  driveController->forwardToIntersection();
  /*
  if(mapGraph->getNumTokens(green) > 0){
    //drop off green tokens
    driveController->turnTo(6);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(green);

    //get back to g1
    driveController->turnTo(2);
    driveController->forwardToIntersection();
  }

  //go to r1
  driveController->turnTo(0);
  driveController->forwardToIntersection();

  if(mapGraph->getNumTokens(red) > 0){
    //drop off red tokens
    driveController->turnTo(7);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(red);

    //get back to r1
    driveController->turnTo(3);
    driveController->forwardToIntersection();
  }

  //go to c1
  driveController->turnTo(2);
  driveController->forwardToIntersection();
  driveController->turnTo(1);

  if(mapGraph->getNumTokens(cyan) > 0){
    //drop off cyan tokens
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(cyan);

    //get back to c1
    driveController->turnTo(5);
    driveController->forwardToIntersection();
  }

  //go to magenta
  driveController->turnTo(4);
  driveController->forwardToIntersection();

  if(mapGraph->getNumTokens(magenta) > 0){
    //drop off magenta tokens
    driveController->turnTo(2);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(magenta);

    //get back to m1
    driveController->turnTo(6);
    driveController->forwardToIntersection();
  }

  //go to yellow box
  driveController->turnTo(4);
  driveController->forwardToIntersection();

  if(mapGraph->getNumTokens(yellow) > 0){
    //drop off yellow tokens
    driveController->turnTo(3);
    driveController->forwardToIntersection();
    move(FWD);
    delay(1000);
    stop();
    tokenController->depositTokens(yellow);
  }

  //go to the white box
  driveController->turnTo(6);
  driveController->forwardToIntersection();

}
 */
/*
void round2(){
	int inventory[6];
  time_t startTime = second();
  time_t endTime = 360 + startTime;
} */
/*
void round1(){
	int inventory[7];
  time_t startTime = second();
  time_t endTime = 300 + startTime; //5 minutes

  //start off at white box
  //go to the square that's closest to the gray box
  //go around said box and pick up tokens

  //once you hit y4 go to y2, traverse around the square
  //once you hit each's color's edge 2, check if we can despoit
  //after going once, if enough time deposit last tokens that nearest to you

  //Start at White Box closest to the yellow
  for (int i = 0; i < 5; i++) {
    driveController->forwardToIntersection();
  }

  driveController->turn45(false, 2);

  //---------------------------------------------------
  //          GO AROUND SQUARE 4 PHRASE

  ///Go to y4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //Go to m4
  driveController->turn45(true,2);
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //can we drop coins at MAGENTA
  if(mapGraph->getNumTokens(magenta) == 2){
    driveController->turn45(false,2);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(magenta);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,2);
  }

  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if can drop off CYAN tokens
  if(mapGraph->getNumTokens(cyan) == 2){
    driveController->turn45(false,1);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(cyan);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,1);
  } else {
    driveController->turn45(true,2);
  }

  //go to r4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off RED tokens
  if(mapGraph->getNumTokens(red) == 2){
    driveController->turn45(false,1);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(red);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,1);
  } else {
    driveController->turn45(true,2);
  }

  //go to g4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off GREEN tokens
  if (mapGraph->getNumTokens(green) == 2) {
    driveController->turn45(false,2);
    for (int i = 0; i < 4; i++) {
       driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(green);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,2);
  }

  //go to b4
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off BLUE tokens
  if (mapGraph->getNumTokens(blue) == 2) {
    driveController->turn45(false,2);
    for (int i = 0; i < 4; i++) {
       driveController->forwardToIntersection();
    }
    driveController->move(FWD);
    delay(1000);
    driveController->stop();
    tokenController->depositTokens(magenta);
    driveController->turn45(false,4);
    for (int i = 0; i < 4; i++) {
      driveController->forwardToIntersection();
    }
    driveController->turn45(false,1);
  }  else {
    driveController->turn45(true,2);
  }

  ///go to y4
  driveController->forwardToIntersection();

  //---------------------------------------------------
  //          GO AROUND SQUARE 2 PHRASE

  //go to y2
  driveController->turn45(false,1);
  driveController->forwardToIntersection();
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  //check if we can drop off YELLOW tokens
  if (mapGraph->getNumTokens(yellow) == 2) {
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();

    driveController->move(FWD);
    delay(1000);
    driveController->stop();

    tokenController->depositTokens(yellow);
    driveController->turn45(false,4);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();
    driveController->turn45(false,1);
  } else {
    driveController->turn45(true,2);
  }


  //go to m2
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  if (mapGraph0>getNumTokens(magenta) >= 2) {
    driveController->turn45(false,2);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();

    driveController->move(FWD);
    delay(1000);
    driveController->stop();

    tokenController->depositTokens(magenta);
    driveController->turn45(false,4);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();
    driveController->turn45(false,2);
  }

  //go to cyan2
  driveController->forwardToIntersection();
  tokenController->pickUpToken();

  if (mapGraph0>getNumTokens(cyan) >= 2) {
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();

    driveController->move(FWD);
    delay(1000);
    driveController->stop();

    tokenController->depositTokens(magenta);
    driveController->turn45(false,1);
    driveController->forwardToIntersection();
    driveController->forwardToIntersection();
    driveController->turn45(false,2);
  } else {
    driveController->turna45(true,2);
  }




}

/*
void forwardToIntersection(){
	while(getData() != getNextIntersection())
		moveForward();
}

void updateInventory(Node::Color c, int[] inventory){
  inventory[c]++;
}

void depositIfEnough(Node::Color c, int min, int current){
	if(current >= min)
		tokenControl::depositTokens();
}

Node::Color whichSide(){
	moveForward(distance to colored square);
	return getColor();
}
*/
