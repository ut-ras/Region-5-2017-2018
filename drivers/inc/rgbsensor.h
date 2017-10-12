#include <stdnt.h>
class rgbsensor {
public:
    //Method to get raw color values
    uint8_t[] getColorValues();

    //Method to get the filtered color from hardware team
    uint8_t getColor();

}
