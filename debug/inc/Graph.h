
#include "Node.h"

class Graph		//class or struct?
{
protected:	
	int V;
	// Hashmap<Node, List<Node>>
	// Hashmap or array enum-->token count
	Node *nodeList;  	//should the position in the list of index i reflect the relative position to i? 
						//have 8[?] positions for each list, and NULL nodes for directions that don't
						//use an array instead? Index for each of the 8 cardinal directions

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
