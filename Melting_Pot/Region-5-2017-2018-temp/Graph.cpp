
#include "Graph.h"
#include <Arduino.h>

Graph::Graph() {
  //Serial.println("Graph Test - inside init");
  //delay(1000);
	//bruteForceInit();
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
  Serial.println("Graph Test - inside bf init");
  delay(500);

	int nodeCounter;

  redBox = new Node();
	red1 = new Node();
	red2 = new Node();
	red3 = new Node();
	red4 = new Node();
	red5 = new Node();
  greenBox = new Node();
	green1 = new Node();
	green2 = new Node();
	green3 = new Node();
	green4 = new Node();
	green5 = new Node();
  blueBox = new Node();
	blue1 = new Node();
	blue2 = new Node();
	blue3 = new Node();
	blue4 = new Node();
	blue5 = new Node();
  yellowBox = new Node();
	yellow1 = new Node();
	yellow2 = new Node();
	yellow3 = new Node();
	yellow4 = new Node();
	 yellow5 = new Node();
  magentaBox = new Node();
	 magenta1 = new Node();
	 magenta2 = new Node();
	magenta3 = new Node();
	 magenta4 = new Node();
	magenta5 = new Node();
  cyanBox = new Node();
	cyan1 = new Node();
	 cyan2 = new Node();
	 cyan3 = new Node();
	 cyan4 = new Node();
	 cyan5 = new Node();
  greyBox = new Node();
	 nullNode = new Node();


	//Red
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
	greyBox->setName(Name::X);
	greyBox->setVisited(false);

	//empty Nodes for blank spaces
	nullNode->setAsNull();

  Serial.println("Graph Test - nodes created bf init");
  delay(500);

  //this works
  Serial.println(cyan4->toString());

/////////////////////   Now set up each individual adjacency lists and add them to the hash map and iterator  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  Node* adj2[37][8] = {
			  { nullNode, nullNode, nullNode, red1, nullNode, nullNode, nullNode, nullNode},		//each element represents a direction:
				{ nullNode, nullNode, cyan1, red2, green1, nullNode, nullNode, nullNode}, 	//{ up, up-right, right, down-right, down, down-left, left, up-left}
				{ nullNode, nullNode, cyan2, red3, green2, nullNode, nullNode, nullNode},
				{ nullNode, nullNode, cyan3, red4, green3, nullNode, nullNode, nullNode},
				{ nullNode, nullNode, cyan4, red5, green4, nullNode, nullNode, nullNode},
				{ nullNode, nullNode, cyan5, greyBox, green5, nullNode, nullNode, nullNode},
				{ nullNode, nullNode, green1, nullNode, nullNode, nullNode, nullNode, nullNode},
				{ red1, nullNode, green2, nullNode, blue1, nullNode, nullNode, nullNode},
				{ red2, nullNode, green3, nullNode, blue2, nullNode, nullNode, nullNode},
				{ red3, nullNode, green4, nullNode, blue3, nullNode, nullNode, nullNode},
				{ red4, nullNode, green5, nullNode, blue4, nullNode, nullNode, nullNode},
				{ red5, nullNode, greyBox, nullNode, blue5, nullNode, nullNode, nullNode},
				{ nullNode, blue1, nullNode, nullNode, nullNode, nullNode, nullNode, nullNode},
				{ green1, blue2, yellow1, nullNode, nullNode, nullNode, nullNode, nullNode},
				{ green2, blue3, yellow2, nullNode, nullNode, nullNode, nullNode, nullNode},
				{ green3, blue4, yellow3, nullNode, nullNode, nullNode, nullNode, nullNode},
				{ green4, blue5, yellow4, nullNode, nullNode, nullNode, nullNode, nullNode},
				{ green5, greyBox, yellow5, nullNode, nullNode, nullNode, nullNode, nullNode},
				{ nullNode, nullNode, nullNode, nullNode, nullNode, nullNode, nullNode, yellow1},
				{ magenta1, nullNode, nullNode, nullNode, nullNode, nullNode, blue1, yellow2},
				{ magenta2, nullNode, nullNode, nullNode, nullNode, nullNode, blue2, yellow3},
				{ magenta3, nullNode, nullNode, nullNode, nullNode, nullNode, blue3, yellow4},
				{ magenta4, nullNode, nullNode, nullNode, nullNode, nullNode, blue4, yellow5},
				{ magenta5, nullNode, nullNode, nullNode, nullNode, nullNode, blue5, greyBox},
				{ nullNode, nullNode, nullNode, nullNode, nullNode, nullNode, magenta1, nullNode},
				{ cyan1, nullNode, nullNode, nullNode, yellow1, nullNode, magenta2, nullNode},
				{ cyan2, nullNode, nullNode, nullNode, yellow2, nullNode, magenta3, nullNode},
				{ cyan3, nullNode, nullNode, nullNode, yellow3, nullNode, magenta4, nullNode},
				{ cyan4, nullNode, nullNode, nullNode, yellow4, nullNode, magenta5, nullNode},
				{ cyan5, nullNode, nullNode, nullNode, yellow5, nullNode, greyBox, nullNode},
				{ nullNode, nullNode, nullNode, nullNode, nullNode, cyan1, nullNode, nullNode},
				{ nullNode, nullNode, nullNode, nullNode, magenta1, cyan2, red1, nullNode},
				{ nullNode, nullNode, nullNode, nullNode, magenta2, cyan3, red2, nullNode},
				{ nullNode, nullNode, nullNode, nullNode, magenta3, cyan4, red3, nullNode},
				{ nullNode, nullNode, nullNode, nullNode, magenta4, cyan5, red4, nullNode},
				{ nullNode, nullNode, nullNode, nullNode, magenta5, greyBox, red5, nullNode},
				{ nullNode, cyan5, magenta5, yellow5, nullNode, blue5, green5, red5} };


  //this does not work
  //array is not being created correctly for some reason
  Serial.println(adj2[0][0]->toString());
  
  int r = 0;
  int c = 0;
  for (r = 0; r < 37; r++) {
    for (c = 0; c < 8; c++) {
      Serial.print("[");
      Serial.print(adj2[r][c]->toString());
      Serial.print("]");
      delay(500);
    }
    Serial.print("\n");
  }
  
  Serial.println("Graph Test - array created bf init");
  delay(500);

  memcpy(adj, adj2, sizeof(adj2));


  //Serial.println("Graph Test - memcpy done bf init");
  //delay(1000);

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

  Serial.println("Graph Test - end of bf init\n");
  delay(500);
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

/* TESTS */



//call in loop or setup or wherever, it will stop at end
void Graph::graphTest() {
  Serial.println("Graph Test - inside graph test\n");
  delay(1000);

  Graph gA;
  Node *endNode = gA.getNode(Name::X); //so we're ending in the center
  //Serial.print("end node: ");
  //Serial.println(endNode->toString());
  delay(500);

  int loopPath[6] = {0, 0, 2, 4, 4, 1};
  int numPathDirs;

  gA.setCurrentNode(gA.getNode(Name::Bl1));
  gA.setCurrentDirection(0);
  numPathDirs = 6;  //loopPath.size();

  //Serial.println("Current Node is: " + g->getCurrentNode() + "\nCurrent Direction is: " + g->getCurrentDirection());
  int nextDir;
  Node *currentNode;
  Node *nextNode;
  for(int i=0; currentNode->getName() != endNode->getName(); i++) {
    Serial.print("Traversal reached node: ");
    delay(500);
    Serial.println(currentNode->toString());
    delay(500);

    /*if(currentNode->getName() != expectedNames[i]){
      Serial.println("Graph traversal test failed on step %d, node: %s and actual %s\n", i, currentNode->getName());
    }*/

    nextDir = loopPath[i % numPathDirs];
    nextNode = gA.getNeighbor(currentNode, nextDir);

    Serial.println("Found next node");
    delay(500);

    gA.setCurrentNode(nextNode);
    currentNode = gA.getCurrentNode();

    Serial.println("Set Next Node");
    delay(500);


    Serial.println("End of Loop");
    delay(500);
  }

  while(1);

}

void Graph::printRawGraph() {
  int r = 0;
  int c = 0;

  for (r = 0; r < 37; r++) {
    for (c = 0; c < 8; c++) {
      Serial.print("[");
      Node * current = adj[r][c];
      Serial.print(current->getName());
      Serial.print("]");
    }
    Serial.print("\n");
  }
}
