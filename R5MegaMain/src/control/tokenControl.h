/* Class for controlling sensors that interface with the token control system
 * stepper motor, servo pulley, electromagnet, upwards facing color sensor
 * picking up tokens, storing tokens, releasing tokens
 */

/* Required libraries (sketch/include library/manage libraries to add)
 * Adafruit_TCS34725
 */

 #ifndef TOKENCONTROL_H
 #define TOKENCONTROL_H

#include "Graph.h"
#include "Node.h"
#include "../drivers/stepper.h"
#include "../drivers/r5servo.h"
#include "../drivers/magnet.h"
#include "../drivers/rgbsensor.h"

class tokenControl {

public:
    //Constructor
    tokenControl(Graph * m);

    /* Picks up a token on the field
     * assuming the robot is in the
     * correct position, then stores
     * it into the appropriate funnel.
     */
    int pickUpToken();

    /* Picks up from the funnel and
     * deposits onto the field, all
     * tokens of the input colour c.
     */
    void depositAllTokens(int c);

    /* Picks up from the funnel and
     * deposits onto the field, one
     * tokens of the input colour c.
     */
    void depositOneToken(int c);

    //****TEST FUNCTIONS***
    //Rotates the disk to each colour then resets
    void goToEveryColour();

    //Drops the pulley, turns on the magnet, then brings up the picked up pulley
    void pickUpTokenTest();

    //Picks up a token from a funnel then brings it to the center
    void pickupFromFunnelTest(int colour);



private:
    //Rotates the token disk to input colour
    //Prereq: Magnet is centered
    void rotateDiskToColor(int c);

    //Rotates the token disk to input colour
    //Prereq: Magnet is over RGB sensor
    void rotateDiskFromSensor(int c);

    //Rotates the disk to the sensor and reads input
    //Prereq: Disk is centered
    int readColour();

    //Resets the disk from input colour to center
    //Prereq: Magnet is at c
    void resetDisk(int c);

    //Deposits held tokens into the funnel
    //Prereq: Over a funnel
    void depositInFunnel();

    //Deposits the token into the tube
    //Prereq: over tube
    void depositInTube();

    //Picks up tokens from the funnel
    //Prereq: Over a funnel
    void pickupFromFunnel();

    //Moves the pulley to and from the field
    void moveToField(int angle);

    Graph * mapGraph;    //for token storage information and updating nodes with new info

    r5servo *pulleyController;
    stepper *diskController;
    magnet *magnetController;
    rgbsensor *colourSensor;
};
#endif
