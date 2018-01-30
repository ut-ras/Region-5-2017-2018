

void setupTestArrayLine()
{
	Serial.begin(9600);

	arrayline();
}


 void loopArrayLineTest(){
    int i;
    lineSensor = getLineSensor();
    
    for(int i = 0; i<8; i++)
    {
        Serial.print(lineSensor[i]);
    }
    
    Serial.println();
 
}