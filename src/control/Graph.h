#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

#define NUMBER_OF_NODES 37

class Graph	{
  
protected:
  Node* iterator[NUMBER_OF_NODES];  //list of all nodes, in order of Node Name enum
	Node* adj[NUMBER_OF_NODES][8];    //adjacency lists for each node, in order of Node Name enum

	int numTokens[7];   //token storage information
 
	Node* currentNode;    //currrent location
	int currentDirection;	//integer 0-7 to determine the current direction of the bot. 0=north, 1=NE, etc

public:
	Graph();

  //token storage information
  int getNumTokens(int c);  //c is Color
  int addToken(int c);    //c is Color
  
	Node* getNode(Name n);  	//n is Name
  Node* getNeighbor(Node *n, int direction);
  Node* moveInDirection(int dir);

  Node* getCurrentNode();
	void setCurrentNode(Node *n);

  int getCurrentDirection();
	void setCurrentDirection(int direction);

  void graphTest();

  void printSerial();
	char* toString();



private:
    void bruteForceInit();
      
    Node  redBox,  red1,  red2,  red3,  red4,  red5,
		 greenBox,  green1,  green2,  green3,  green4,  green5,
		 blueBox,  blue1,  blue2,  blue3,  blue4,  blue5,
     yellowBox,  yellow1,  yellow2,  yellow3,  yellow4,  yellow5,
		 magentaBox,   magenta1,  magenta2,  magenta3,  magenta4,  magenta5,
		 cyanBox,  cyan1,  cyan2,  cyan3,  cyan4,  cyan5,
		 greyBox,  nullNode;
};

#endif
