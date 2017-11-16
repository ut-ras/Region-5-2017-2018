
#include "Node.h"
#include <HashMap.h>
//https://playground.arduino.cc/Code/HashMap		 graph[0](Node,Node[8]);

class Graph		//class or struct?
{
protected:
	int V;
	HashMap<Node, Node[8]> graph;
	int[7] numTokens;
	Node currentNode;
	int currentDirection;	//integer 0-7 to determine the current direction of the bot. 0=north, 1=NE, etc

public:
	Graph();
	Node* getNode(Node::Name n);
	int getNumTokens(Node::Color c);
	int addToken(Node::Color c);
	Node getCurrentNode();
	int getCurrentDirection();
	Node getNeighbor(Node n, int direction);

private:
	void bruteForceInit();
}
