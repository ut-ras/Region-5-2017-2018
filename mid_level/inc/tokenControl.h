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
    void depositTokens(Node::Color c);

private:
	void lowerMagnet(double distance);
	void raiseMagnet(double distance);
	Node::Color findColor();
	void rotateDisk(Node::Color c);
	void depositInFunnel();
	void reset();	//goes back over hole

}
