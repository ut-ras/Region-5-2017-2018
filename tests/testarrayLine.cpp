#include "testArrayLine.h"

testArrayLine::testArrayLine()
{
	Serial.begin(9600);

	arrayline();
}


void testArrayLine::loopArrayLineTest(){
    int i;
    lineSensor = getLineSensor();
    
    for(int i = 0; i<8; i++)
    {
        Serial.print(lineSensor[i]);
    }
    
    Serial.println();
 
}