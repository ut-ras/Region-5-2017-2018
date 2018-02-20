
#include "Graph.h"


Graph::Graph()
{
	bruteForceInit();
}

/* returns the node the bot is currently located at */
Node* Graph::getCurrentNode() {
		return currentNode;
}

/* returns the current cardinal direction the bot is facing */
int Graph::getCurrentDirection() {
	return currentDirection;
}

/*sets the current node to the Node n*/
void Graph::setCurrentNode(Node *n){
	currentNode = n;
}

/*sets the current direction to the direction*/
void Graph::setCurrentDirection(int direction){
	currentDirection = direction;
}

/* returns the neighbor (Node) in the cardinal direction DIRECTION of N */
Node* Graph::getNeighbor(Node *n, int direction) {
	return adj[n->getName()][direction];
}

Node* Graph::moveInDirection(int dir) {
	currentNode = getNeighbor(currentNode, dir);
	currentDirection = dir;
}

Node* Graph::getNode(Name n) {
	for (int i = 0; i < NUMBER_OF_NODES; i++) {
		if (iterator[i]->getName() == n) {
			return iterator[i];
		}
	}
	return NULL;
}

/* BEAST of a function to create the entire map:
   	- Map stored as hashmap between node and adjacency list (array)
    - Nodes also stored in array by name enum (index) for quick iteration
*/
void Graph::bruteForceInit() {
	int nodeCounter;

	//Red
	Node* redBox = new Node();		//create the nodes
	Node* red1 = new Node();
	Node* red2 = new Node();
	Node* red3 = new Node();
	Node* red4 = new Node();
	Node* red5 = new Node();
	redBox->setName(Name::R);	//assign the enums (names)
	red1->setName(Name::R1);
	red2->setName(Name::R2);
	red3->setName(Name::R3);
	red4->setName(Name::R4);
	red5->setName(Name::R5);
	redBox->setVisited(false);			//initialize visited boolean
	red1->setVisited(false);
	red2->setVisited(false);
	red3->setVisited(false);
	red4->setVisited(false);
	red5->setVisited(false);

	//Green
	Node* greenBox = new Node();
	Node* green1 = new Node();
	Node* green2 = new Node();
	Node* green3 = new Node();
	Node* green4 = new Node();
	Node* green5 = new Node();
	greenBox->setName(Name::G);
	green1->setName(Name::G1);
	green2->setName(Name::G2);
	green3->setName(Name::G3);
	green4->setName(Name::G4);
	green5->setName(Name::G5);
	greenBox->setVisited(false);
	green1->setVisited(false);
	green2->setVisited(false);
	green3->setVisited(false);
	green4->setVisited(false);
	green5->setVisited(false);

	//Blue
	Node* blueBox = new Node();
	Node* blue1 = new Node();
	Node* blue2 = new Node();
	Node* blue3 = new Node();
	Node* blue4 = new Node();
	Node* blue5 = new Node();
	blueBox->setName(Name::Bl);
	blue1->setName(Name::Bl1);
	blue2->setName(Name::Bl2);
	blue3->setName(Name::Bl3);
	blue4->setName(Name::Bl4);
	blue5->setName(Name::Bl5);
	blueBox->setVisited(false);
	blue1->setVisited(false);
	blue2->setVisited(false);
	blue3->setVisited(false);
	blue4->setVisited(false);
	blue5->setVisited(false);

	//Yellow
	Node* yellowBox = new Node();
	Node* yellow1 = new Node();
	Node* yellow2 = new Node();
	Node* yellow3 = new Node();
	Node* yellow4 = new Node();
	Node* yellow5 = new Node();
	yellowBox->setName(Name::Y);
	yellow1->setName(Name::Y1);
	yellow2->setName(Name::Y2);
	yellow3->setName(Name::Y3);
	yellow4->setName(Name::Y4);
	yellow5->setName(Name::Y5);
	yellowBox->setVisited(false);
	yellow1->setVisited(false);
	yellow2->setVisited(false);
	yellow3->setVisited(false);
	yellow4->setVisited(false);
	yellow5->setVisited(false);

	//Magenta
	Node* magentaBox = new Node();
	Node* magenta1 = new Node();
	Node* magenta2 = new Node();
	Node* magenta3 = new Node();
	Node* magenta4 = new Node();
	Node* magenta5 = new Node();
	magentaBox->setName(Name::M);
	magenta1->setName(Name::M1);
	magenta2->setName(Name::M2);
	magenta3->setName(Name::M3);
	magenta4->setName(Name::M4);
	magenta5->setName(Name::M5);
	magentaBox->setVisited(false);
	magenta1->setVisited(false);
	magenta2->setVisited(false);
	magenta3->setVisited(false);
	magenta4->setVisited(false);
	magenta5->setVisited(false);

	//Cyan
	Node* cyanBox = new Node();
	Node* cyan1 = new Node();
	Node* cyan2 = new Node();
	Node* cyan3 = new Node();
	Node* cyan4 = new Node();
	Node* cyan5 = new Node();
	cyanBox->setName(Name::C);
	cyan1->setName(Name::C1);
	cyan2->setName(Name::C2);
	cyan3->setName(Name::C3);
	cyan4->setName(Name::C4);
	cyan5->setName(Name::C5);
	cyanBox->setVisited(false);
	cyan1->setVisited(false);
	cyan2->setVisited(false);
	cyan3->setVisited(false);
	cyan4->setVisited(false);
	cyan5->setVisited(false);

	//Grey
	Node* greyBox = new Node();
	greyBox->setName(Name::X);
	greyBox->setVisited(false);

/////////////////////   Now set up each individual adjacency lists and add them to the hash map and iterator  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  Node * adj2[37][8] = {	{NULL, NULL, NULL, red1, NULL, NULL, NULL, NULL},		//each element represents a direction:
								{NULL, NULL, cyan1, red2, green1, NULL, NULL, NULL}, 	//{up, up-right, right, down-right, down, down-left, left, up-left}
					{NULL, NULL, cyan2, red3, green2, NULL, NULL, NULL},
					{NULL, NULL, cyan3, red4, green3, NULL, NULL, NULL},
							{NULL, NULL, cyan4, red5, green4, NULL, NULL, NULL},
					{NULL, NULL, cyan5, greyBox, green5, NULL, NULL, NULL},
					{NULL, NULL, green1, NULL, NULL, NULL, NULL, NULL},
					{red1, NULL, green2, NULL, blue1, NULL, NULL, NULL},
				{red2, NULL, green3, NULL, blue2, NULL, NULL, NULL},
				{red3, NULL, green4, NULL, blue3, NULL, NULL, NULL},
				{red4, NULL, green5, NULL, blue4, NULL, NULL, NULL},
				{red5, NULL, greyBox, NULL, blue5, NULL, NULL, NULL},
				{NULL, blue1, NULL, NULL, NULL, NULL, NULL, NULL},
				{green1, blue2, yellow1, NULL, NULL, NULL, NULL, NULL},
				{green2, blue3, yellow2, NULL, NULL, NULL, NULL, NULL},
				{green3, blue4, yellow3, NULL, NULL, NULL, NULL, NULL},
				{green4, blue5, yellow4, NULL, NULL, NULL, NULL, NULL},
				{green5, greyBox, yellow5, NULL, NULL, NULL, NULL, NULL},
				{NULL, NULL, NULL, NULL, NULL, NULL, NULL, yellow1},
				{magenta1, NULL, NULL, NULL, NULL, NULL, blue1, yellow2},
				{magenta2, NULL, NULL, NULL, NULL, NULL, blue2, yellow3},
				{magenta3, NULL, NULL, NULL, NULL, NULL, blue3, yellow4},
				{magenta4, NULL, NULL, NULL, NULL, NULL, blue4, yellow5},
				{magenta5, NULL, NULL, NULL, NULL, NULL, blue5, greyBox},
				{NULL, NULL, NULL, NULL, NULL, NULL, magenta1, NULL},
				{cyan1, NULL, NULL, NULL, yellow1, NULL, magenta2, NULL},
				{cyan2, NULL, NULL, NULL, yellow2, NULL, magenta3, NULL},
				{cyan3, NULL, NULL, NULL, yellow3, NULL, magenta4, NULL},
				{cyan4, NULL, NULL, NULL, yellow4, NULL, magenta5, NULL},
				{cyan5, NULL, NULL, NULL, yellow5, NULL, greyBox, NULL},
				{NULL, NULL, NULL, NULL, NULL, cyan1, NULL, NULL},
				{NULL, NULL, NULL, NULL, magenta1, cyan2, red1, NULL},
				{NULL, NULL, NULL, NULL, magenta2, cyan3, red2, NULL},
				{NULL, NULL, NULL, NULL, magenta3, cyan4, red3, NULL},
				{NULL, NULL, NULL, NULL, magenta4, cyan5, red4, NULL},
				{NULL, NULL, NULL, NULL, magenta5, greyBox, red5, NULL},
				{NULL, cyan5, magenta5, yellow5, NULL, blue5, green5, red5} };

  memcpy(adj, adj2, 37*8*sizeof(Node *));
	//Red


	iterator[0] = redBox;
	iterator[1] = red1;
	iterator[2] = red2;
	iterator[3] = red3;
	iterator[4] = red4;
	iterator[5] = red5;


	//Green

	iterator[6] = greenBox;
	iterator[7] = green1;
	iterator[8] = green2;
	iterator[9] = green3;
	iterator[10] = green4;
	iterator[11] = green5;

	//Blue

	/*
	graph[12](blueBox, adjB);
	graph[13](blue1, adjBl1);
	graph[14](blue2, adjBl2);
	graph[15](blue3, adjBl3);
	graph[16](blue4, adjBl4);
	graph[17](blue5, adjBl5);
	*/
	iterator[12] = blueBox;
	iterator[13] = blue1;
	iterator[14] = blue2;
	iterator[15] = blue3;
	iterator[16] = blue4;
	iterator[17] = blue5;

	//Yellows:

	/*
	graph[18](yellowBox, adjY);
	graph[19](yellow1, adjY1);
	graph[20](yellow2, adjY2);
	graph[21](yellow3, adjY3);
	graph[22](yellow4, adjY4);
	graph[23](yellow5, adjY5);
	*/
	iterator[18] = yellowBox;
	iterator[19] = yellow1;
	iterator[20] = yellow2;
	iterator[21] = yellow3;
	iterator[22] = yellow4;
	iterator[23] = yellow5;

	//Magentas:

	/*
	graph[24](magentaBox, adjM);
	graph[25](magenta1, adjM1);
	graph[26](magenta2, adjM2);
	graph[27](magenta3, adjM3);
	graph[28](magenta4, adjM4);
	graph[29](magenta5, adjM5);
	*/
	iterator[24] = magentaBox;
	iterator[25] = magenta1;
	iterator[26] = magenta2;
	iterator[27] = magenta3;
	iterator[28] = magenta4;
	iterator[29] = magenta5;

	//Cyans:

	/*
	graph[30](cyanBox, adjC);
	graph[31](cyan1, adjC1);
	graph[32](cyan2, adjC2);
	graph[33](cyan3, adjC3);
	graph[34](cyan4, adjC4);
	graph[35](cyan5, adjC5);
	*/
	iterator[30] = cyanBox;
	iterator[31] = cyan1;
	iterator[32] = cyan2;
	iterator[33] = cyan3;
	iterator[34] = cyan4;
	iterator[35] = cyan5;

	//Greys:

	//graph[36](greyBox, adjX)
	iterator[36] = greyBox;
}

/* Iterates through every node and creates a string describing the map's current state such that
    - Nodes are '/' delimited
    - per-node information is formatted as described in Node::toString()
 */
const char* Graph::toString() {
	char* result;
	for(int i=0; i < NUMBER_OF_NODES; i++) {
		*result += iterator[i]->toString();		// legal syntax in C++ ?
		if(i != NUMBER_OF_NODES)
			*result += '/'; 		// nodes will be '/' delimited
	}
}
