
#include "Node.h"

class Graph		//class or struct?
{
protected:	
	int V;
	Node *nodeList;  	//should the position in the list of index i reflect the relative position to i? 
						//have 8[?] positions for each list, and NULL nodes for directions that don't
						//use an array instead

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
