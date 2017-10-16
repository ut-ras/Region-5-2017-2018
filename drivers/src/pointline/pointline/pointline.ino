/*
Code to use a single point line sensor
 
 */

int sensorPin = A7;    // select the input pin for the Line sensor
int sensorValue = 0;  // variable to store the value coming from the sensor
typedef enum {LINE, NOLINE, UNKNOWN} lineStatus;
#define BLACK 2700
#define WHITE 1000
void setup() {
  //Start serial Monitor 
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
}

lineStatus getValue(int sensorValue)
{
    if(sensorValue<WHITE)
  {
    return NOLINE;
  }
  if(sensorValue>BLACK)
  {
    return LINE;
  }
  return UNKNOWN;
}
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // turn the ledPin on
  digitalWrite(GREEN_LED, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  lineStatus line = getValue(sensorValue);
  if(line==LINE)
  {
    Serial.println("BLACK");
  }
  if(line==NOLINE)
  {
    Serial.println("WHITE");
  }
  // turn the ledPin off:        
  digitalWrite(GREEN_LED, LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(1.0);                  
}
