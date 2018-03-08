
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
	if (n < 0 || n >= NUMBER_OF_NODES) {
    return NULL;
	}
	return iterator[n];
}

/* BEAST of a function to create the entire map:
   	- Map stored as hashmap between node and adjacency list (array)
    - Nodes also stored in array by name enum (index) for quick iteration
*/
void Graph::bruteForceInit() {
  Serial.println("Graph Test - inside bf init");
  delay(500);

	int nodeCounter;

  redBox = new Node(Name::R, red);
	red1 = new Node(Name::R1, red);
	red2 = new Node(Name::R2, red);
	red3 = new Node(Name::R3, red);
	red4 = new Node(Name::R4, red);
	red5 = new Node(Name::R5, red);
  greenBox = new Node(Name::G, green);
	green1 = new Node(Name::G1, green);
	green2 = new Node(Name::G2, green);
	green3 = new Node(Name::G3, green);
	green4 = new Node(Name::G4, green);
	green5 = new Node(Name::G5, green);
  blueBox = new Node(Name::Bl, blue);
	blue1 = new Node(Name::Bl1, blue);
	blue2 = new Node(Name::Bl2, blue);
	blue3 = new Node(Name::Bl3, blue);
	blue4 = new Node(Name::Bl4, blue);
	blue5 = new Node(Name::Bl5, blue);
  yellowBox = new Node(Name::Y, yellow);
	yellow1 = new Node(Name::Y1, yellow);
	yellow2 = new Node(Name::Y2, yellow);
	yellow3 = new Node(Name::Y3, yellow);
	yellow4 = new Node(Name::Y4, yellow);
	yellow5 = new Node(Name::Y5, yellow);
  magentaBox = new Node(Name::M, magenta);
	magenta1 = new Node(Name::M1, magenta);
	magenta2 = new Node(Name::M2, magenta);
	magenta3 = new Node(Name::M3, magenta);
	magenta4 = new Node(Name::M4, magenta);
	magenta5 = new Node(Name::M5, magenta);
  cyanBox = new Node(Name::C, cyan);
	cyan1 = new Node(Name::C1, cyan);
	cyan2 = new Node(Name::C2, cyan);
	cyan3 = new Node(Name::C3, cyan);
	cyan4 = new Node(Name::C4, cyan);
	cyan5 = new Node(Name::C5, cyan);
  greyBox = new Node(Name::X, grey);
	nullNode = new Node();
  nullNode->setAsNull();
	

  Serial.println("Graph Test - nodes created bf init");
  delay(500);
  
  // Now set up each individual adjacency lists and add them to the hash map and iterator  \\\\\\\\\\
  
  adj[0][0] =  nullNode;
  adj[0][1] =  nullNode;
  adj[0][2] =  nullNode;
  adj[0][3] =  red1;
  adj[0][4] =  nullNode;
  adj[0][5] =  nullNode;
  adj[0][6] =  nullNode;
  adj[0][7] =  nullNode;
  adj[1][0] =  nullNode;
  adj[1][1] =  nullNode;
  adj[1][2] =  cyan1;
  adj[1][3] =  red2;
  adj[1][4] =  green1;
  adj[1][5] =  nullNode;
  adj[1][6] =  nullNode;
  adj[1][7] =  nullNode;
  adj[2][0] =  nullNode;
  adj[2][1] =  nullNode;
  adj[2][2] =  cyan2;
  adj[2][3] =  red3;
  adj[2][4] =  green2;
  adj[2][5] =  nullNode;
  adj[2][6] =  nullNode;
  adj[2][7] =  nullNode;
  adj[3][0] =  nullNode;
  adj[3][1] =  nullNode;
  adj[3][2] =  cyan3;
  adj[3][3] =  red4;
  adj[3][4] =  green3;
  adj[3][5] =  nullNode;
  adj[3][6] =  nullNode;
  adj[3][7] =  nullNode;
  adj[4][0] =  nullNode;
  adj[4][1] =  nullNode;
  adj[4][2] =  cyan4;
  adj[4][3] =  red5;
  adj[4][4] =  green4;
  adj[4][5] =  nullNode;
  adj[4][6] =  nullNode;
  adj[4][7] =  nullNode;
  adj[5][0] =  nullNode;
  adj[5][1] =  nullNode;
  adj[5][2] =  cyan5;
  adj[5][3] =  greyBox;
  adj[5][4] =  green5;
  adj[5][5] =  nullNode;
  adj[5][6] =  nullNode;
  adj[5][7] =  nullNode;
  adj[6][0] =  nullNode;
  adj[6][1] =  nullNode;
  adj[6][2] =  green1;
  adj[6][3] =  nullNode;
  adj[6][4] =  nullNode;
  adj[6][5] =  nullNode;
  adj[6][6] =  nullNode;
  adj[6][7] =  nullNode;
  adj[7][0] =  red1;
  adj[7][1] =  nullNode;
  adj[7][2] =  green2;
  adj[7][3] =  nullNode;
  adj[7][4] =  blue1;
  adj[7][5] =  nullNode;
  adj[7][6] =  nullNode;
  adj[7][7] =  nullNode;
  adj[8][0] =  red2;
  adj[8][1] =  nullNode;
  adj[8][2] =  green3;
  adj[8][3] =  nullNode;
  adj[8][4] =  blue2;
  adj[8][5] =  nullNode;
  adj[8][6] =  nullNode;
  adj[8][7] =  nullNode;
  adj[9][0] =  red3;
  adj[9][1] =  nullNode;
  adj[9][2] =  green4;
  adj[9][3] =  nullNode;
  adj[9][4] =  blue3;
  adj[9][5] =  nullNode;
  adj[9][6] =  nullNode;
  adj[9][7] =  nullNode;
  adj[10][0] =  red4;
  adj[10][1] =  nullNode;
  adj[10][2] =  green5;
  adj[10][3] =  nullNode;
  adj[10][4] =  blue4;
  adj[10][5] =  nullNode;
  adj[10][6] =  nullNode;
  adj[10][7] =  nullNode;
  adj[11][0] =  red5;
  adj[11][1] =  nullNode;
  adj[11][2] =  greyBox;
  adj[11][3] =  nullNode;
  adj[11][4] =  blue5;
  adj[11][5] =  nullNode;
  adj[11][6] =  nullNode;
  adj[11][7] =  nullNode;
  adj[12][0] =  nullNode;
  adj[12][1] =  blue1;
  adj[12][2] =  nullNode;
  adj[12][3] =  nullNode;
  adj[12][4] =  nullNode;
  adj[12][5] =  nullNode;
  adj[12][6] =  nullNode;
  adj[12][7] =  nullNode;
  adj[13][0] =  green1;
  adj[13][1] =  blue2;
  adj[13][2] =  yellow1;
  adj[13][3] =  nullNode;
  adj[13][4] =  nullNode;
  adj[13][5] =  nullNode;
  adj[13][6] =  nullNode;
  adj[13][7] =  nullNode;
  adj[14][0] =  green2;
  adj[14][1] =  blue3;
  adj[14][2] =  yellow2;
  adj[14][3] =  nullNode;
  adj[14][4] =  nullNode;
  adj[14][5] =  nullNode;
  adj[14][6] =  nullNode;
  adj[14][7] =  nullNode;
  adj[15][0] =  green3;
  adj[15][1] =  blue4;
  adj[15][2] =  yellow3;
  adj[15][3] =  nullNode;
  adj[15][4] =  nullNode;
  adj[15][5] =  nullNode;
  adj[15][6] =  nullNode;
  adj[15][7] =  nullNode;
  adj[16][0] =  green4;
  adj[16][1] =  blue5;
  adj[16][2] =  yellow4;
  adj[16][3] =  nullNode;
  adj[16][4] =  nullNode;
  adj[16][5] =  nullNode;
  adj[16][6] =  nullNode;
  adj[16][7] =  nullNode;
  adj[17][0] =  green5;
  adj[17][1] =  greyBox;
  adj[17][2] =  yellow5;
  adj[17][3] =  nullNode;
  adj[17][4] =  nullNode;
  adj[17][5] =  nullNode;
  adj[17][6] =  nullNode;
  adj[17][7] =  nullNode;
  adj[18][0] =  nullNode;
  adj[18][1] =  nullNode;
  adj[18][2] =  nullNode;
  adj[18][3] =  nullNode;
  adj[18][4] =  nullNode;
  adj[18][5] =  nullNode;
  adj[18][6] =  nullNode;
  adj[18][7] =  yellow1;
  adj[19][0] =  magenta1;
  adj[19][1] =  nullNode;
  adj[19][2] =  nullNode;
  adj[19][3] =  nullNode;
  adj[19][4] =  nullNode;
  adj[19][5] =  nullNode;
  adj[19][6] =  blue1;
  adj[19][7] =  yellow2;
  adj[20][0] =  magenta2;
  adj[20][1] =  nullNode;
  adj[20][2] =  nullNode;
  adj[20][3] =  nullNode;
  adj[20][4] =  nullNode;
  adj[20][5] =  nullNode;
  adj[20][6] =  blue2;
  adj[20][7] =  yellow3;
  adj[21][0] =  magenta3;
  adj[21][1] =  nullNode;
  adj[21][2] =  nullNode;
  adj[21][3] =  nullNode;
  adj[21][4] =  nullNode;
  adj[21][5] =  nullNode;
  adj[21][6] =  blue3;
  adj[21][7] =  yellow4;
  adj[22][0] =  magenta4;
  adj[22][1] =  nullNode;
  adj[22][2] =  nullNode;
  adj[22][3] =  nullNode;
  adj[22][4] =  nullNode;
  adj[22][5] =  nullNode;
  adj[22][6] =  blue4;
  adj[22][7] =  yellow5;
  adj[23][0] =  magenta5;
  adj[23][1] =  nullNode;
  adj[23][2] =  nullNode;
  adj[23][3] =  nullNode;
  adj[23][4] =  nullNode;
  adj[23][5] =  nullNode;
  adj[23][6] =  blue5;
  adj[23][7] =  greyBox;
  adj[24][0] =  nullNode;
  adj[24][1] =  nullNode;
  adj[24][2] =  nullNode;
  adj[24][3] =  nullNode;
  adj[24][4] =  nullNode;
  adj[24][5] =  nullNode;
  adj[24][6] =  magenta1;
  adj[24][7] =  nullNode;
  adj[25][0] =  cyan1;
  adj[25][1] =  nullNode;
  adj[25][2] =  nullNode;
  adj[25][3] =  nullNode;
  adj[25][4] =  yellow1;
  adj[25][5] =  nullNode;
  adj[25][6] =  magenta2;
  adj[25][7] =  nullNode;
  adj[26][0] =  cyan2;
  adj[26][1] =  nullNode;
  adj[26][2] =  nullNode;
  adj[26][3] =  nullNode;
  adj[26][4] =  yellow2;
  adj[26][5] =  nullNode;
  adj[26][6] =  magenta3;
  adj[26][7] =  nullNode;
  adj[27][0] =  cyan3;
  adj[27][1] =  nullNode;
  adj[27][2] =  nullNode;
  adj[27][3] =  nullNode;
  adj[27][4] =  yellow3;
  adj[27][5] =  nullNode;
  adj[27][6] =  magenta4;
  adj[27][7] =  nullNode;
  adj[28][0] =  cyan4;
  adj[28][1] =  nullNode;
  adj[28][2] =  nullNode;
  adj[28][3] =  nullNode;
  adj[28][4] =  yellow4;
  adj[28][5] =  nullNode;
  adj[28][6] =  magenta5;
  adj[28][7] =  nullNode;
  adj[29][0] =  cyan5;
  adj[29][1] =  nullNode;
  adj[29][2] =  nullNode;
  adj[29][3] =  nullNode;
  adj[29][4] =  yellow5;
  adj[29][5] =  nullNode;
  adj[29][6] =  greyBox;
  adj[29][7] =  nullNode;
  adj[30][0] =  nullNode;
  adj[30][1] =  nullNode;
  adj[30][2] =  nullNode;
  adj[30][3] =  nullNode;
  adj[30][4] =  nullNode;
  adj[30][5] =  cyan1;
  adj[30][6] =  nullNode;
  adj[30][7] =  nullNode;
  adj[31][0] =  nullNode;
  adj[31][1] =  nullNode;
  adj[31][2] =  nullNode;
  adj[31][3] =  nullNode;
  adj[31][4] =  magenta1;
  adj[31][5] =  cyan2;
  adj[31][6] =  red1;
  adj[31][7] =  nullNode;
  adj[32][0] =  nullNode;
  adj[32][1] =  nullNode;
  adj[32][2] =  nullNode;
  adj[32][3] =  nullNode;
  adj[32][4] =  magenta2;
  adj[32][5] =  cyan3;
  adj[32][6] =  red2;
  adj[32][7] =  nullNode;
  adj[33][0] =  nullNode;
  adj[33][1] =  nullNode;
  adj[33][2] =  nullNode;
  adj[33][3] =  nullNode;
  adj[33][4] =  magenta3;
  adj[33][5] =  cyan4;
  adj[33][6] =  red3;
  adj[33][7] =  nullNode;
  adj[34][0] =  nullNode;
  adj[34][1] =  nullNode;
  adj[34][2] =  nullNode;
  adj[34][3] =  nullNode;
  adj[34][4] =  magenta4;
  adj[34][5] =  cyan5;
  adj[34][6] =  red4;
  adj[34][7] =  nullNode;
  adj[35][0] =  nullNode;
  adj[35][1] =  nullNode;
  adj[35][2] =  nullNode;
  adj[35][3] =  nullNode;
  adj[35][4] =  magenta5;
  adj[35][5] =  greyBox;
  adj[35][6] =  red5;
  adj[35][7] =  nullNode;
  adj[36][0] =  nullNode;
  adj[36][1] =  cyan5;
  adj[36][2] =  magenta5;
  adj[36][3] =  yellow5;
  adj[36][4] =  nullNode;
  adj[36][5] =  blue5;
  adj[36][6] =  green5;
  adj[36][7] =  red5;
  
  
  Serial.println("Graph Test - array created bf init");
  delay(500);

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
	iterator[12] = blueBox;
	iterator[13] = blue1;
	iterator[14] = blue2;
	iterator[15] = blue3;
	iterator[16] = blue4;
	iterator[17] = blue5;

	//Yellows:
	iterator[18] = yellowBox;
	iterator[19] = yellow1;
	iterator[20] = yellow2;
	iterator[21] = yellow3;
	iterator[22] = yellow4;
	iterator[23] = yellow5;

	//Magentas:
	iterator[24] = magentaBox;
	iterator[25] = magenta1;
	iterator[26] = magenta2;
	iterator[27] = magenta3;
	iterator[28] = magenta4;
	iterator[29] = magenta5;

	//Cyans:
	iterator[30] = cyanBox;
	iterator[31] = cyan1;
	iterator[32] = cyan2;
	iterator[33] = cyan3;
	iterator[34] = cyan4;
	iterator[35] = cyan5;

	//Greys:
	iterator[36] = greyBox;

  Serial.println("Graph Test - end of bf init\n");
  delay(500);
}


void Graph::printRawGraph() {
  int r = 0;
  int c = 0;

  Serial.println("Node\t\tAdjacency List");
   
  for (r = 0; r < 37; r++) {
    Serial.print("[");
    Serial.print(iterator[r]->nameToString());
    if (iterator[r]->getMapColor() == red) {
      Serial.print("]   \t");
    }else {
      Serial.print("]\t");
    }
    
    for (c = 0; c < 8; c++) {
      Node * current = adj[r][c];
      Serial.print("[");
      Serial.print(current->toString());
      if (current->getMapColor() == red) {
        Serial.print("]   \t\t");
      }else {
        Serial.print("]\t\t");
      }
      delay(30);
    }
    Serial.print("\n");
  }
}

/* Not tested - Iterates through every node and creates a string describing the map's current state such that
    - Nodes are '/' delimited
    - per-node information is formatted as described in Node::toString()  */
const char* Graph::toString() {
	char* result;
	for(int i=0; i < NUMBER_OF_NODES; i++) {
		result = iterator[i]->toString();		// legal syntax in C++ ?
		Serial.print(result);
	}
}




/* TESTS */

//call in loop or setup or wherever, it will stop at end
void Graph::graphTest() {
  //Serial.println("Graph Test - inside graph test\n");
  delay(1000);

  Graph gA;
  Node *endNode = gA.getNode(Name::X); //so we're ending in the center
  //Serial.print("end node: ");
  //Serial.println(endNode->toString());
  //delay(500);

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
    //Serial.print("Traversal reached node: ");
    //delay(500);
    //Serial.println(currentNode->toString());
    //delay(500);

    /*if(currentNode->getName() != expectedNames[i]){
      Serial.println("Graph traversal test failed on step %d, node: %s and actual %s\n", i, currentNode->getName());
    }*/

    nextDir = loopPath[i % numPathDirs];
    nextNode = gA.getNeighbor(currentNode, nextDir);

    //Serial.println("Found next node");
    //delay(500);

    gA.setCurrentNode(nextNode);
    currentNode = gA.getCurrentNode();

    //Serial.println("Set Next Node");
    //delay(500);

    //Serial.println("End of Loop");
    //delay(500);

    Serial.println(gA.toString());
  }

  while(1);

}


