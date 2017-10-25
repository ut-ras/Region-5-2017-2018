
#include "Node.h"
#define NUMBER_OF_NODES 31

class Graph
{
protected:	
	int V;
	Node** adjList;  //array of NodePointers

public:
	Graph()
	{
		bruteForceInit();
	}

	//need functions to move through map and get/set node details?

private:
	void bruteForceInit()
	{
		//creates the map with all of the connections and specific nodes
		//how to do this more easily?
	}

}
