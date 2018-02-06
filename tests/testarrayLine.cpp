#include "../drivers/inc/arrayline.h"

bool* lineSensor;
arrayline* line;
void setupTestArrayLine()
{
	line = new arrayline();
	lineSensor = new bool[8];
}


void loopArrayLineTest(){
    int i;
    
    for(int i = 0; i<8; i++)
    {
        Serial.print(lineSensor[i]);
    }
    
    Serial.println();

}