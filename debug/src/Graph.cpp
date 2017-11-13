
#include "../inc/Graph.h"
#include <Hashmap.h>
#define NUMBER_OF_NODES 31

void Graph::Graph()
{
	bruteForceInit();
}

Node Graph::getCurrentNode() {
		return currentNode;
}

int Graph::getCurrentDirection() {
	return currentDirection;
}

void Graph::bruteForceInit()
{
	//Red
	Node redBox = new Node();		//create the nodes
	Node red1 = new Node();
	Node red2 = new Node();
	Node red3 = new Node();
	Node red4 = new Node();
	redBox.Name = Node::Name::R;	//assign the enums (names)
	red1.Name = Node::Name::R1;
	red2.Name = Node::Name::R2;
	red3.Name = Node::Name::R3;
	red4.Name = Node::Name::R4;
	redBox.visited = false;			//initialize visited boolean
	red1.visited = false;
	red2.visited = false;
	red3.visited = false;
	red4.visited = false;

	//Green
	Node greenBox = new Node();
	Node green1 = new Node();
	Node green2 = new Node();
	Node green3 = new Node();
	Node green4 = new Node();
	greenBox.Name = Node::Name::G;
	green1.Name = Node::Name::G1;
	green2.Name = Node::Name::G2;
	green3.Name = Node::Name::G3;
	green4.Name = Node::Name::G4;
	greenBox.visited = false;
	green1.visited = false;
	green2.visited = false;
	green3.visited = false;
	green4.visited = false;

	//Blue
	Node blueBox = new Node();
	Node blue1 = new Node();
	Node blue2 = new Node();
	Node blue3 = new Node();
	Node blue4 = new Node();
	blueBox.Name = Node::Name::B;
	blue1.Name = Node::Name::B1;
	blue2.Name = Node::Name::B2;
	blue3.Name = Node::Name::B3;
	blue4.Name = Node::Name::B4;
	blueBox.visited = false;
	blue1.visited = false;
	blue2.visited = false;
	blue3.visited = false;
	blue4.visited = false;

	//Yellow
	Node yellowBox = new Node();
	Node yellow1 = new Node();
	Node yellow2 = new Node();
	Node yellow3 = new Node();
	Node yellow4 = new Node();
	yellowBox.Name = Node::Name::Y;
	yellow1.Name = Node::Name::Y1;
	yellow2.Name = Node::Name::Y2;
	yellow3.Name = Node::Name::Y3;
	yellow4.Name = Node::Name::Y4;
	yellowBox.visited = false;
	yellow1.visited = false;
	yellow2.visited = false;
	yellow3.visited = false;
	yellow4.visited = false;

	//Magenta
	Node magentaBox = new Node();
	Node magenta1 = new Node();
	Node magenta2 = new Node();
	Node magenta3 = new Node();
	Node magenta4 = new Node();
	magentaBox.Name = Node::Name::M;
	magenta1.Name = Node::Name::M1;
	magenta2.Name = Node::Name::M2;
	magenta3.Name = Node::Name::M3;
	magenta4.Name = Node::Name::M4;
	magentaBox.visited = false;
	magenta1.visited = false;
	magenta2.visited = false;
	magenta3.visited = false;
	magenta4.visited = false;

	//Cyan
	Node cyanBox = new Node();
	Node cyan1 = new Node();
	Node cyan2 = new Node();
	Node cyan3 = new Node();
	Node cyan4 = new Node();
	cyanBox.Name = Node::Name::C;
	cyan1.Name = Node::Name::C1;
	cyan2.Name = Node::Name::C2;
	cyan3.Name = Node::Name::C3;
	cyan4.Name = Node::Name::C4;
	cyanBox.visited = false;
	cyan1.visited = false;
	cyan2.visited = false;
	cyan3.visited = false;
	cyan4.visited = false;

	//Grey
	Node greyBox = new Node();
	greyBox.Name = Node::Name::X;
	greyBox.visited = false;

/////////////////////   Now set up each individual adjacency lists andd add them to the hash map   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
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

	//Greys:
	Node adjX  [8] = {NULL, cyan4, magenta4, yellow4, NULL, blue4, green4, red4};
	graph[30](greyBox, adjX)
}
