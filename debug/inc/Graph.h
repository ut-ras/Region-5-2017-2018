
#include "Node.h"
#include <HashMap.h>
//https://playground.arduino.cc/Code/HashMap		 graph[0](Node,Node[8]);

class Graph		//class or struct?
{
protected:
	int V;
	HashMap<Node, Node[8]> graph;
	int[7] numTokens;

public:
	Graph();
	Node* getNode(Node::Name n);
	int getNumTokens(Node::Color c);
	int addToken(Node::Color c);

private:
	void bruteForceInit();
}
