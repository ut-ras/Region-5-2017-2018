#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

#define NUMBER_OF_NODES 37

class Graph	{
protected:
	int V;
	//HashMap<Node*, Node*[8]> graph;
	Node* adj[NUMBER_OF_NODES][8];

	int numTokens[7];
	Node* currentNode;
	int currentDirection;	//integer 0-7 to determine the current direction of the bot. 0=north, 1=NE, etc
	Node* iterator[NUMBER_OF_NODES];	//need to be able to quickly iterate through every node

public:
	Graph();
	Node* getNode(Name n);  	//n is Name
	int getNumTokens(int c); 	//c is Color
	int addToken(int c); 		//c is Color
	Node* getCurrentNode();
	void setCurrentNode(Node *n);
	void setCurrentDirection(int direction);
	int getCurrentDirection();
	Node* getNeighbor(Node *n, int direction);
	char* toString();
	Node* moveInDirection(int dir);
  	void graphTest();
  	void printRawGraph();

	void bruteForceInit();
  

private:
    Node  redBox,  red1,  red2,  red3,  red4,  red5,
		 greenBox,  green1,  green2,  green3,  green4,  green5,
		 blueBox,  blue1,  blue2,  blue3,  blue4,  blue5,
     yellowBox,  yellow1,  yellow2,  yellow3,  yellow4,  yellow5,
		 magentaBox,   magenta1,  magenta2,  magenta3,  magenta4,  magenta5,
		 cyanBox,  cyan1,  cyan2,  cyan3,  cyan4,  cyan5,
		 greyBox,  nullNode;
};

#endif
