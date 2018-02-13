/* Class for controlling sensors that interface with the token control system
 * stepper motor, servo pulley, electromagnet, upwards facing color sensor
 * picking up tokens, storing tokens, releasing tokens
 */

#include "Node.h"
#include "stepper.h"
#include "servo.h"
#include "rgbsensor.h"
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
    Node::Color pickUpToken();

    /* Picks up from the funnel and
     * deposits onto the field, the
     * tokens of the input colour c.
     */
    void depositTokens(Node::Color c);

private:
    //Rotates the token disk to input colour
    //Prereq: Magnet is centered
    void rotateDiskToColor(Node::Color c);
    //Resets the disk from input colour to center
    //Prereq: Magnet is at c
    void resetDisk(Node::Color c);
    //Deposits held tokens into the funnel
    //Prereq: Over a funnel
    void depositInFunnel();
    //Picks up tokens from the funnel
    //Prereq: Over a funnel
    void pickupFromFunnel();

    servo pulleyController;
    stepper diskController;
    rgbsensor tokenReader;
    magnet magnetController;
};
