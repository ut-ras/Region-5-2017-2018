#include "Log.h"

Log::Log() {
 writeString(StartSequence); 
}

void Log::logNode(Node n) {
    writeString(n.toString())
}

void Log::clearLog()  {
     for(int i = 0; i<dataAddr+1; i++)
    {
    EEPROM.write(i, 255);
}

}

static void Log::writeString(String str)
{
    if(str.length()+dataAddr> MAX_MEMORY)
    {
    return;
}   
    for(int i = 0; i<str.length(); i++)
    {
       EEPROM.write(dataAddr, str.charAt(i));
       dataAddr = dataAddr+1;  
   }
}
