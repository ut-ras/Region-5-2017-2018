
#include "Node.h"
#include <Hashmap.h>
#define NUMBER_OF_NODES 31

void Graph::Graph()
{
	bruteForceInit();
}

void Graph::bruteForceInit()
{
	//creates the map with all of the connections and specific nodes
	//how to do this more easily?
	createNodes();
	initRed();
	initGreen();
	initBlue();
	initYellow();
	initMagenta();
	initCyan();
	initGrey();
}

void Graph::createNodes()
{
	for (int i = 0; i < 31; i++)
	{
		Node noob = new Node();
		noob.Name = i;
		noob.visited = false;
		Node adj [8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
		this.graph
	}	
}

