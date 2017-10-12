#define LINESENSOR_SIZE 8
class arrayline {
public:

    //Get line sensor array for line sensor values
    bool[LINESENSOR_SIZE] getLineSensor();

    //Check if any of the 8 sensors are true
    bool isLine();

}
