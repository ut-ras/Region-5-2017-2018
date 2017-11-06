
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

//Creates nodes and adjaccency lists and adds them to the HashMap
void Graph::createNodes()
{
	//Red
	Node redBox = new Node();
	redBox.Name = Node::Name::R;	 
	redBox.visited = false;
	Node red1 = new Node();
	red1.Name = Node::Name::R1;	 
	red1.visited = false;
	Node red2 = new Node();
	red2.Name = Node::Name::R2;	 
	red2.visited = false;
	Node red3 = new Node();
	red3.Name = Node::Name::R3;	 
	red3.visited = false;
	Node red4 = new Node();
	red4.Name = Node::Name::R4;	 
	red4.visited = false;
	//Green
	Node greenBox = new Node();
	greenBox.Name = Node::Name::G;	 
	greenBox.visited = false;
	Node green1 = new Node();
	green1.Name = Node::Name::G1;	 
	green1.visited = false;
	Node green2 = new Node();
	green2.Name = Node::Name::G2;	 
	green2.visited = false;
	Node green3 = new Node();
	green3.Name = Node::Name::G3;	 
	green3.visited = false;
	Node green4 = new Node();
	green4.Name = Node::Name::G4;	 
	green4.visited = false;
	//Blue
	Node blueBox = new Node();
	blueBox.Name = Node::Name::B;	 
	blueBox.visited = false;
	Node blue1 = new Node();
	blue1.Name = Node::Name::B1;	 
	blue1.visited = false;
	Node blue2 = new Node();
	blue2.Name = Node::Name::B2;	 
	blue2.visited = false;
	Node blue3 = new Node();
	blue3.Name = Node::Name::B3;	 
	blue3.visited = false;
	Node blue4 = new Node();
	blue4.Name = Node::Name::B4;	 
	blue4.visited = false;	
	//Yellow
	Node yellowBox = new Node();
	yellowBox.Name = Node::Name::Y;	 
	yellowBox.visited = false;
	Node yellow1 = new Node();
	yellow1.Name = Node::Name::Y1;	 
	yellow1.visited = false;
	Node yellow2 = new Node();
	yellow2.Name = Node::Name::Y2;	 
	yellow2.visited = false;
	Node yellow3 = new Node();
	yellow3.Name = Node::Name::Y3;	 
	yellow3.visited = false;
	Node yellow4 = new Node();
	yellow4.Name = Node::Name::Y4;	 
	yellow4.visited = false;
	//Magenta
	Node magentaBox = new Node();
	magentaBox.Name = Node::Name::M;	 
	magentaBox.visited = false;
	Node magenta1 = new Node();
	magenta1.Name = Node::Name::M1;	 
	magenta1.visited = false;
	Node magenta2 = new Node();
	magenta2.Name = Node::Name::M2;	 
	magenta2.visited = false;
	Node magenta3 = new Node();
	magenta3.Name = Node::Name::M3;	 
	magenta3.visited = false;
	Node magenta4 = new Node();
	magenta4.Name = Node::Name::M4;	 
	magenta4.visited = false;
	//Cyan
	Node cyanBox = new Node();
	cyanBox.Name = Node::Name::C;	 
	cyanBox.visited = false;
	Node cyan1 = new Node();
	cyan1.Name = Node::Name::C1;	 
	cyan1.visited = false;
	Node cyan2 = new Node();
	cyan2.Name = Node::Name::C2;	 
	cyan2.visited = false;
	Node cyan3 = new Node();
	cyan3.Name = Node::Name::C3;	 
	cyan3.visited = false;
	Node cyan4 = new Node();
	cyan4.Name = Node::Name::C4;	 
	cyan4.visited = false;
	//Grey
	Node greyBox = new Node();
	greyBox.Name = Node::Name::X;	 
	greyBox.visited = false;

	//Now set up each individual adjacency lists
	Node adjR [8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};	//each element represents a direction
	graph[i](noob, adj);

}

void initRed()
{
	for(int i=0; i<5; i++)
	{

	}
}


