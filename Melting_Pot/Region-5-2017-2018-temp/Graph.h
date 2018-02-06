

//#include <HashMap.h>
#include "Node.h"
//https://playground.arduino.cc/Code/HashMap		 graph[0](Node,Node[8]);
#define NUMBER_OF_NODES 31

class Graph		//class or struct?
{
protected:
	int V;
	//HashMap<Node*, Node*[8]> graph;
	Node* adj[37][8];
	int numTokens[7];
	Node* currentNode;
	int currentDirection;	//integer 0-7 to determine the current direction of the bot. 0=north, 1=NE, etc
	Node* iterator[NUMBER_OF_NODES];	//need to be able to quickly iterate through every node

public:
	Graph();
	Node* getNode(int n);  //n is Name
	int getNumTokens(int c); //c is Color
	int addToken(int c); //c is Color
	Node getCurrentNode();
	int getCurrentDirection();
	Node getNeighbor(Node n, int direction);
	String toString();
	Node* moveInDirection(int dir);

private:
	void bruteForceInit();
};
