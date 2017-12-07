/* Class for controlling sensors that interface with the token control system
 * stepper motor, servo pulley, electromagnet, upwards facing color sensor
 * picking up tokens, storing tokens, releasing tokens
 */

#include "../../debug/inc/Node.h"
#include "../../drivers/inc/stepper.h"
#include "../../drivers/inc/servo.h"
#include "../../drivers/inc/rgbsensor.h"
#include "../../drivers/inc/magnet.h"

class tokenControl {

public:
    //Constructor
    tokenControl();
    /* Picks up a token on the field
     * assuming the robot is in the
     * correct position.
     */
    void pickUpToken();

    /* Stores a picked up token into
     * the funnel in the appropriate slot
     */
    Node::Color storeToken();

    /* Picks up from the funnel and
     * deposits onto the field, the
     * tokens of the input colour c.
     */
    void depositTokens(Node::Color c);

private:
    //Lower magnet distance
    void lowerMagnet(double distance);
    //Raise magnet distance
    void raiseMagnet(double distance);
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