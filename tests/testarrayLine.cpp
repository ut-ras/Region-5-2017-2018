#include "./drivers/inc/arrayline.h"

bool* lineSensor;
void setupTestArrayLine()
{
	Serial.begin(9600);
	arrayline line = arrayline();
	lineSensor = new bool[8];
}


void loopArrayLineTest(){
  /*  int i;
    lineSensor = [false];
    
    for(int i = 0; i<8; i++)
    {
        Serial.print(lineSensor[i]);
    }
    
    Serial.println();
 */
}