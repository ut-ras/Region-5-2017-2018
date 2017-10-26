
#include "Node.h"
#define NUMBER_OF_NODES 31

class Graph		//class or struct?
{
protected:	
	int V;
	Node *nodeList;  	//should the position in the list of index i reflect the relative position to i? 
						//have 8[?] positions for each list, and NULL nodes for directions that don't

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

		nodeList = malloc(V * sizeOf(Node));
		Node* ptr = nodeList;
		for(int i=0; i<31; i++)
		{
			if(i%5 == 0)
				Node newNode = new Node();		// node for drop-off points 
			else
				Node newNode = new Intersection();
			newNode.name = i;
			newNode.visited = false;
			nodeList[i] = newNode;

			//setUp the adjacency list for each node
			//bruteForceAdjListInit(){};

			
		}
	}

}
