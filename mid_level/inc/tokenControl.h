/* Class for controlling sensors that interface with the token control system
 * stepper motor, servo pulley, electromagnet, upwards facing color sensor
 * picking up tokens, storing tokens, releasing tokens
 */

#include "Node.h";

class tokenControl {

public:
    tokenControl();
    bool pickUpToken();
    Node::Color storeToken();

private:
	void lowerMagnet();
	void raiseMagnet();
	Node::Color findColor();
	void rotateDisk(Node::Color c);
	
}
