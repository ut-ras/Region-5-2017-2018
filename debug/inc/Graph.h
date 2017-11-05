
#include "Node.h"
#include <HashMap.h>
//https://playground.arduino.cc/Code/HashMap		 graph[0](Node,Node[8]);

class Graph		//class or struct?
{
protected:
	int V;
	HashMap<Node, Node[8]> graph;

public:
	Graph();
	Node* getNode(Node::Name n);

private:
	void bruteForceInit();
}
