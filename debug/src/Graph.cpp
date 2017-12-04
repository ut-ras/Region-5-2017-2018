
#include "../inc/Graph.h"
#include <Hashmap.h>

void Graph::Graph()
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
void Graph::setCurrentNode(Node n){
	currentNode = n;
}

/*sets the current direction to the direction*/
void Graph::setCurrentDirection(int direction){
	currentDirection = direction;
}

/* returns the neighbor (Node) in the cardinal direction DIRECTION of N */
Node* Graph::getNeighbor(Node::Node n, int direction) {
	Node[8] adj = graph.getValueOf(n);
	return adj[direction];
}

Node* Graph::moveInDirection(int dir) {
	currentNode = getNeighbor(currentNode, dir);
	currentDirection = dir;
}

Node* Graph::getNode(Node::Name n) {
	//TODO iterate through hashmap and find node with name


}

/* BEAST of a function to create the entire map:
   	- Map stored as hashmap between node and adjacency list (array)
    - Nodes also stored in array by name enum (index) for quick iteration
*/
void Graph::bruteForceInit()
{
	int nodeCounter;

	//Red
	Node redBox = new Node();		//create the nodes
	Node red1 = new Node();
	Node red2 = new Node();
	Node red3 = new Node();
	Node red4 = new Node();
	redBox.setName(Node::Name::R);	//assign the enums (names)
	red1.setName(Node::Name::R1);
	red2.setName(Node::Name::R2);
	red3.setName(Node::Name::R3);
	red4.setName(Node::Name::R4);
	redBox.setVisited(false);			//initialize visited boolean
	red1.setVisited(false);
	red2.setVisited(false);
	red3.setVisited(false);
	red4.setVisited(false);

	//Green
	Node greenBox = new Node();
	Node green1 = new Node();
	Node green2 = new Node();
	Node green3 = new Node();
	Node green4 = new Node();
	greenBox.setName(Node::Name::G);
	green1.setName(Node::Name::G1);
	green2.setName(Node::Name::G2);
	green3.setName(Node::Name::G3);
	green4.setName(Node::Name::G4);
	greenBox.setVisited(false);
	green1.setVisited(false);
	green2.setVisited(false);
	green3.setVisited(false);
	green4.setVisited(false);

	//Blue
	Node blueBox = new Node();
	Node blue1 = new Node();
	Node blue2 = new Node();
	Node blue3 = new Node();
	Node blue4 = new Node();
	blueBox.setName(Node::Name::B);
	blue1.setName(Node::Name::B1);
	blue2.setName(Node::Name::B2);
	blue3.setName(Node::Name::B3);
	blue4.setName(Node::Name::B4);
	blueBox.setVisited(false);
	blue1.setVisited(false);
	blue2.setVisited(false);
	blue3.setVisited(false);
	blue4.setVisited(false);

	//Yellow
	Node yellowBox = new Node();
	Node yellow1 = new Node();
	Node yellow2 = new Node();
	Node yellow3 = new Node();
	Node yellow4 = new Node();
	yellowBox.setName(Node::Name::Y);
	yellow1.setName(Node::Name::Y1);
	yellow2.setName(Node::Name::Y2);
	yellow3.setName(Node::Name::Y3);
	yellow4.setName(Node::Name::Y4);
	yellowBox.setVisited(false);
	yellow1.setVisited(false);
	yellow2.setVisited(false);
	yellow3.setVisited(false);
	yellow4.setVisited(false);

	//Magenta
	Node magentaBox = new Node();
	Node magenta1 = new Node();
	Node magenta2 = new Node();
	Node magenta3 = new Node();
	Node magenta4 = new Node();
	magentaBox.setName(Node::Name::M);
	magenta1.setName(Node::Name::M1);
	magenta2.setName(Node::Name::M2);
	magenta3.setName(Node::Name::M3);
	magenta4.setName(Node::Name::M4);
	magentaBox.setVisited(false);
	magenta1.setVisited(false);
	magenta2.setVisited(false);
	magenta3.setVisited(false);
	magenta4.setVisited(false);

	//Cyan
	Node cyanBox = new Node();
	Node cyan1 = new Node();
	Node cyan2 = new Node();
	Node cyan3 = new Node();
	Node cyan4 = new Node();
	cyanBox.setName(Node::Name::C);
	cyan1.setName(Node::Name::C1);
	cyan2.setName(Node::Name::C2);
	cyan3.setName(Node::Name::C3);
	cyan4.setName(Node::Name::C4);
	cyanBox.setVisited(false);
	cyan1.setVisited(false);
	cyan2.setVisited(false);
	cyan3.setVisited(false);
	cyan4.setVisited(false);

	//Grey
	Node greyBox = new Node();
	greyBox.setName(Node::Name::X);
	greyBox.setVisited(false);

/////////////////////   Now set up each individual adjacency lists and add them to the hash map and iterator  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//Red
	Node adjR  [8] = {NULL, NULL, NULL, red1, NULL, NULL, NULL, NULL};		//each element represents a direction:
	Node adjR1 [8] = {NULL, NULL, cyan1, red2, green1, NULL, NULL, NULL};	//{up, up-right, right, down-right, down, down-left, left, up-left}
	Node adjR2 [8] = {NULL, NULL, cyan2, red3, green2, NULL, NULL, NULL};
	Node adjR3 [8] = {NULL, NULL, cyan3, red4, green3, NULL, NULL, NULL};
	Node adjR4 [8] = {NULL, NULL, cyan4, greyBox, green4, NULL, NULL, NULL};
	graph[0](redBox, adjR);
	graph[1](red1, adjR1);
	graph[2](red2, adjR2);
	graph[3](red3, adjR3);
	graph[4](red4, adjR4);
	iterator[0] = redBox;
	iterator[1] = red1;
	iterator[2] = red2;
	iterator[3] = red3;
	iterator[4] = red4;

	//Green
	Node adjG  [8] = {NULL, NULL, green1, NULL, NULL, NULL, NULL, NULL};
	Node adjG1 [8] = {red1, NULL, green2, NULL, blue1, NULL, NULL, NULL};
	Node adjG2 [8] = {red2, NULL, green3, NULL, blue2, NULL, NULL, NULL};
	Node adjG3 [8] = {red3, NULL, green4, NULL, blue3, NULL, NULL, NULL};
	Node adjG4 [8] = {red4, NULL, greyBox, NULL, blue4, NULL, NULL, NULL};
	graph[5](greenBox, adjG);
	graph[6](green1, adjG1);
	graph[7](green2, adjG2);
	graph[8](green3, adjG3);
	graph[9](green4, adjG4);
	iterator[5] = greenBox;
	iterator[6] = green1;
	iterator[7] = green2;
	iterator[8] = green3;
	iterator[9] = green4;

	//Blue
	Node adjB  [8] = {NULL, blue1, NULL, NULL, NULL, NULL, NULL, NULL};
	Node adjB1 [8] = {green1, blue2, yellow1, NULL, NULL, NULL, NULL, NULL};
	Node adjB2 [8] = {green2, blue3, yellow2, NULL, NULL, NULL, NULL, NULL};
	Node adjB3 [8] = {green3, blue4, yellow3, NULL, NULL, NULL, NULL, NULL};
	Node adjB4 [8] = {green4, greyBox, yellow4, NULL, NULL, NULL, NULL, NULL};
	graph[10](blueBox, adjB);
	graph[11](blue1, adjB1);
	graph[12](blue2, adjB2);
	graph[13](blue3, adjB3);
	graph[14](blue1, adjB1);
	iterator[10] = blueBox;
	iterator[11] = blue1;
	iterator[12] = blue2;
	iterator[13] = blue3;
	iterator[14] = blue4;

	//Yellows:
	Node adjY  [8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, yellow1};
	Node adjY1 [8] = {magenta1, NULL, NULL, NULL, NULL, NULL, blue1, yellow2};
	Node adjY2 [8] = {magenta2, NULL, NULL, NULL, NULL, NULL, blue2, yellow3};
	Node adjY3 [8] = {magenta3, NULL, NULL, NULL, NULL, NULL, blue3, yellow4};
	Node adjY4 [8] = {magenta4, NULL, NULL, NULL, NULL, NULL, blue4, greyBox};
	graph[15](yellowBox, adjY);
	graph[16](yellow1, adjY1);
	graph[17](yellow2, adjY2);
	graph[18](yellow3, adjY3);
	graph[19](yellow4, adjY4);
	iterator[15] = yellowBox;
	iterator[16] = yellow1;
	iterator[17] = yellow2;
	iterator[18] = yellow3;
	iterator[19] = yellow4;

	//Magentas:
	Node adjM  [8] = {NULL, NULL, NULL, NULL, NULL, NULL, magenta1, NULL};
	Node adjM1 [8] = {cyan1, NULL, NULL, NULL, yellow1, NULL, magenta2, NULL};
	Node adjM2 [8] = {cyan2, NULL, NULL, NULL, yellow2, NULL, magenta3, NULL};
	Node adjM3 [8] = {cyan3, NULL, NULL, NULL, yellow3, NULL, magenta4, NULL};
	Node adjM4 [8] = {cyan4, NULL, NULL, NULL, yellow4, NULL, greyBox, NULL};
	graph[20](magentaBox, adjM);
	graph[21](magenta1, adjM1);
	graph[22](magenta2, adjM2);
	graph[23](magenta3, adjM3);
	graph[24](magenta4, adjM4);
	iterator[20] = magentaBox;
	iterator[21] = magenta1;
	iterator[22] = magenta2;
	iterator[23] = magenta3;
	iterator[24] = magenta4;

	//Cyans:
	Node adjC  [8] = {NULL, NULL, NULL, NULL, NULL, cyan1, NULL, NULL};
	Node adjC1 [8] = {NULL, NULL, NULL, NULL, magenta1, cyan2, red1, NULL};
	Node adjC2 [8] = {NULL, NULL, NULL, NULL, magenta2, cyan3, red2, NULL};
	Node adjC3 [8] = {NULL, NULL, NULL, NULL, magenta3, cyan4, red3, NULL};
	Node adjC4 [8] = {NULL, NULL, NULL, NULL, magenta4, greyBox, red4, NULL};
	graph[25](cyanBox, adjC);
	graph[26](cyan1, adjC1);
	graph[27](cyan2, adjC2);
	graph[28](cyan3, adjC3);
	graph[29](cyan4, adjC4);
	iterator[25] = cyanBox;
	iterator[26] = cyan1;
	iterator[27] = cyan2;
	iterator[28] = cyan3;
	iterator[29] = cyan4;

	//Greys:
	Node adjX  [8] = {NULL, cyan4, magenta4, yellow4, NULL, blue4, green4, red4};
	graph[30](greyBox, adjX)
	iterator[30] = greyBox;
}

/* Iterates through every node and creates a string describing the map's current state such that
    - Nodes are '/' delimited
    - per-node information is formatted as described in Node::toString()
 */
string Graph::toString() {
	string result;
	for(int i=0; i < NUMBER_OF_NODES; i++) {
		result += iterator[i].toString();		// legal syntax in C++ ?
		if(i != NUMBER_OF_NODES)
			result += "/"; 		// nodes will be '/' delimited
	}
}
