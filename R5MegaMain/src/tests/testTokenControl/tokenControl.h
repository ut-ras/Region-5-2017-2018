/* Class for controlling sensors that interface with the token control system
 * stepper motor, servo pulley, electromagnet, upwards facing color sensor
 * picking up tokens, storing tokens, releasing tokens
 */

 #ifndef TOKENCONTROL_H
 #define TOKENCONTROL_H

#include "Node.h"
#include "stepper.h"
#include "r5servo.h"
#include "magnet.h"

class tokenControl {

public:
    //Constructor
    tokenControl();

    /* Picks up a token on the field
     * assuming the robot is in the
     * correct position, then stores
     * it into the appropriate funnel.
     */
    int pickUpToken();

    /* Picks up from the funnel and
     * deposits onto the field, the
     * tokens of the input colour c.
     */
    void depositTokens(int c);

    void initialize();

private:
    //Rotates the token disk to input colour
    //Prereq: Magnet is centered
    void rotateDiskToColor(int c);
    //Resets the disk from input colour to center
    //Prereq: Magnet is at c
    void resetDisk(int c);
    //Deposits held tokens into the funnel
    //Prereq: Over a funnel
    void depositInFunnel();
    //Picks up tokens from the funnel
    //Prereq: Over a funnel
    void pickupFromFunnel();

    r5servo *pulleyController;
    stepper *diskController;
    magnet *magnetController;
};
#endif
