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
    tokenControl();
    void pickUpToken();
    Node::Color storeToken();
    void depositTokens(Node::Color c);

private:
    void lowerMagnet(double distance);
    void raiseMagnet(double distance);
    void rotateDiskToColor(Node::Color c);
    void resetDisk(Node::Color c);
    void depositInFunnel();

    servo pulleyController;
    stepper diskController;
    rgbsensor tokenReader;
    magnet magnetController;
};