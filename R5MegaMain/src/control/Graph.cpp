
#include "Graph.h"
#include <Arduino.h>

Graph::Graph() {
  //Serial.println("Graph Test - inside init");
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

Node* Graph::getNextIntersection() {
  return getNeighbor(currentNode, currentDirection);
}

Node* Graph::getNode(Name n) {
	if (n < 0 || n >= NUMBER_OF_NODES) {
    return NULL;
	}
	return iterator[n];
}


//*****Token Counters*****

void Graph::addToken(int c){
  numTokens[c]++;
}

void Graph::removeToken(int c){
  numTokens[c]--;
}

int Graph::getNumTokens(int c){
  return numTokens[c];
}

/* BEAST of a function to create the entire map:
   	- Map stored as hashmap between node and adjacency list (array)
    - Nodes also stored in array by name enum (index) for quick iteration
*/
void Graph::bruteForceInit() {
  //Serial.println("Graph Test - inside bf init");
  //delay(500);

  redBox = Node(Name::R, red);
	red1 = Node(Name::R1, red);
	red2 = Node(Name::R2, red);
	red3 = Node(Name::R3, red);
	red4 = Node(Name::R4, red);
	red5 = Node(Name::R5, red);
  greenBox = Node(Name::G, green);
	green1 = Node(Name::G1, green);
	green2 = Node(Name::G2, green);
	green3 = Node(Name::G3, green);
	green4 = Node(Name::G4, green);
	green5 = Node(Name::G5, green);
  blueBox = Node(Name::Bl, blue);
	blue1 = Node(Name::Bl1, blue);
	blue2 = Node(Name::Bl2, blue);
	blue3 = Node(Name::Bl3, blue);
	blue4 = Node(Name::Bl4, blue);
	blue5 = Node(Name::Bl5, blue);
  yellowBox = Node(Name::Y, yellow);
	yellow1 = Node(Name::Y1, yellow);
	yellow2 = Node(Name::Y2, yellow);
	yellow3 = Node(Name::Y3, yellow);
	yellow4 = Node(Name::Y4, yellow);
	yellow5 = Node(Name::Y5, yellow);
  magentaBox = Node(Name::M, magenta);
	magenta1 = Node(Name::M1, magenta);
	magenta2 = Node(Name::M2, magenta);
	magenta3 = Node(Name::M3, magenta);
	magenta4 = Node(Name::M4, magenta);
	magenta5 = Node(Name::M5, magenta);
  cyanBox = Node(Name::C, cyan);
	cyan1 = Node(Name::C1, cyan);
	cyan2 = Node(Name::C2, cyan);
	cyan3 = Node(Name::C3, cyan);
	cyan4 = Node(Name::C4, cyan);
	cyan5 = Node(Name::C5, cyan);
  greyBox = Node(Name::X, grey);
	nullNode = Node();
  nullNode.setAsNull();
  
  //Serial.println("Graph Test - nodes created bf init");
  //delay(500);
  
  // Now set up each individual adjacency lists and add them to the hash map and iterator  \\\\\\\\\\
  
  adj[R][0] = &nullNode;
  adj[R][1] = &nullNode;
  adj[R][2] = &nullNode;
  adj[R][3] = &red1;
  adj[R][4] = &nullNode;
  adj[R][5] = &nullNode;
  adj[R][6] = &nullNode;
  adj[R][7] = &nullNode;
  
  adj[R1][0] = &nullNode;
  adj[R1][1] = &nullNode;
  adj[R1][2] = &cyan1;
  adj[R1][3] = &red2;
  adj[R1][4] = &green1;
  adj[R1][5] = &nullNode;
  adj[R1][6] = &nullNode;
  adj[R1][7] = &redBox;
  
  adj[R2][0] = &nullNode;
  adj[R2][1] = &nullNode;
  adj[R2][2] = &cyan2;
  adj[R2][3] = &red3;
  adj[R2][4] = &green2;
  adj[R2][5] = &nullNode;
  adj[R2][6] = &nullNode;
  adj[R2][7] = &red1;
  
  adj[R3][0] = &nullNode;
  adj[R3][1] = &nullNode;
  adj[R3][2] = &cyan3;
  adj[R3][3] = &red4;
  adj[R3][4] = &green3;
  adj[R3][5] = &nullNode;
  adj[R3][6] = &nullNode;
  adj[R3][7] = &red2;
  
  adj[R4][0] = &nullNode;
  adj[R4][1] = &nullNode;
  adj[R4][2] = &cyan4;
  adj[R4][3] = &red5;
  adj[R4][4] = &green4;
  adj[R4][5] = &nullNode;
  adj[R4][6] = &nullNode;
  adj[R4][7] = &red3;
  
  adj[R5][0] = &nullNode;
  adj[R5][1] = &nullNode;
  adj[R5][2] = &cyan5;
  adj[R5][3] = &greyBox;
  adj[R5][4] = &green5;
  adj[R5][5] = &nullNode;
  adj[R5][6] = &nullNode;
  adj[R5][7] = &red4;
  
  adj[G][0] = &nullNode;
  adj[G][1] = &nullNode;
  adj[G][2] = &green1;
  adj[G][3] = &nullNode;
  adj[G][4] = &nullNode;
  adj[G][5] = &nullNode;
  adj[G][6] = &nullNode;
  adj[G][7] = &nullNode;
  
  adj[G1][0] = &red1;
  adj[G1][1] = &nullNode;
  adj[G1][2] = &green2;
  adj[G1][3] = &nullNode;
  adj[G1][4] = &blue1;
  adj[G1][5] = &nullNode;
  adj[G1][6] = &greenBox;
  adj[G1][7] = &nullNode;
  
  adj[G2][0] = &red2;
  adj[G2][1] = &nullNode;
  adj[G2][2] = &green3;
  adj[G2][3] = &nullNode;
  adj[G2][4] = &blue2;
  adj[G2][5] = &nullNode;
  adj[G2][6] = &green1;
  adj[G2][7] = &nullNode;
  
  adj[G3][0] = &red3;
  adj[G3][1] = &nullNode;
  adj[G3][2] = &green4;
  adj[G3][3] = &nullNode;
  adj[G3][4] = &blue3;
  adj[G3][5] = &nullNode;
  adj[G3][6] = &green2;
  adj[G3][7] = &nullNode;
  
  adj[G4][0] = &red4;
  adj[G4][1] = &nullNode;
  adj[G4][2] = &green5;
  adj[G4][3] = &nullNode;
  adj[G4][4] = &blue4;
  adj[G4][5] = &nullNode;
  adj[G4][6] = &green3;
  adj[G4][7] = &nullNode;
  
  adj[G5][0] = &red5;
  adj[G5][1] = &nullNode;
  adj[G5][2] = &greyBox;
  adj[G5][3] = &nullNode;
  adj[G5][4] = &blue5;
  adj[G5][5] = &nullNode;
  adj[G5][6] = &green4;
  adj[G5][7] = &nullNode;
  
  adj[Bl][0] = &nullNode;
  adj[Bl][1] = &blue1;
  adj[Bl][2] = &nullNode;
  adj[Bl][3] = &nullNode;
  adj[Bl][4] = &nullNode;
  adj[Bl][5] = &nullNode;
  adj[Bl][6] = &nullNode;
  adj[Bl][7] = &nullNode;
  
  adj[Bl1][0] = &green1;
  adj[Bl1][1] = &blue2;
  adj[Bl1][2] = &yellow1;
  adj[Bl1][3] = &nullNode;
  adj[Bl1][4] = &nullNode;
  adj[Bl1][5] = &blueBox;
  adj[Bl1][6] = &nullNode;
  adj[Bl1][7] = &nullNode;
  
  adj[Bl2][0] = &green2;
  adj[Bl2][1] = &blue3;
  adj[Bl2][2] = &yellow2;
  adj[Bl2][3] = &nullNode;
  adj[Bl2][4] = &nullNode;
  adj[Bl2][5] = &blue1;
  adj[Bl2][6] = &nullNode;
  adj[Bl2][7] = &nullNode;
  
  adj[Bl3][0] = &green3;
  adj[Bl3][1] = &blue4;
  adj[Bl3][2] = &yellow3;
  adj[Bl3][3] = &nullNode;
  adj[Bl3][4] = &nullNode;
  adj[Bl3][5] = &blue2;
  adj[Bl3][6] = &nullNode;
  adj[Bl3][7] = &nullNode;
  
  adj[Bl4][0] = &green4;
  adj[Bl4][1] = &blue5;
  adj[Bl4][2] = &yellow4;
  adj[Bl4][3] = &nullNode;
  adj[Bl4][4] = &nullNode;
  adj[Bl4][5] = &blue3;
  adj[Bl4][6] = &nullNode;
  adj[Bl4][7] = &nullNode;
  
  adj[Bl5][0] = &green5;
  adj[Bl5][1] = &greyBox;
  adj[Bl5][2] = &yellow5;
  adj[Bl5][3] = &nullNode;
  adj[Bl5][4] = &nullNode;
  adj[Bl5][5] = &blue4;
  adj[Bl5][6] = &nullNode;
  adj[Bl5][7] = &nullNode;
  
  adj[Y][0] = &nullNode;
  adj[Y][1] = &nullNode;
  adj[Y][2] = &nullNode;
  adj[Y][3] = &nullNode;
  adj[Y][4] = &nullNode;
  adj[Y][5] = &nullNode;
  adj[Y][6] = &nullNode;
  adj[Y][7] = &yellow1;
  
  adj[Y1][0] = &magenta1;
  adj[Y1][1] = &nullNode;
  adj[Y1][2] = &nullNode;
  adj[Y1][3] = &yellowBox;
  adj[Y1][4] = &nullNode;
  adj[Y1][5] = &nullNode;
  adj[Y1][6] = &blue1;
  adj[Y1][7] = &yellow2;
  
  adj[Y2][0] = &magenta2;
  adj[Y2][1] = &nullNode;
  adj[Y2][2] = &nullNode;
  adj[Y2][3] = &yellow1;
  adj[Y2][4] = &nullNode;
  adj[Y2][5] = &nullNode;
  adj[Y2][6] = &blue2;
  adj[Y2][7] = &yellow3;
  
  adj[Y3][0] = &magenta3;
  adj[Y3][1] = &nullNode;
  adj[Y3][2] = &nullNode;
  adj[Y3][3] = &yellow2;
  adj[Y3][4] = &nullNode;
  adj[Y3][5] = &nullNode;
  adj[Y3][6] = &blue3;
  adj[Y3][7] = &yellow4;
  
  adj[Y4][0] = &magenta4;
  adj[Y4][1] = &nullNode;
  adj[Y4][2] = &nullNode;
  adj[Y4][3] = &yellow3;
  adj[Y4][4] = &nullNode;
  adj[Y4][5] = &nullNode;
  adj[Y4][6] = &blue4;
  adj[Y4][7] = &yellow5;
  
  adj[Y5][0] = &magenta5;
  adj[Y5][1] = &nullNode;
  adj[Y5][2] = &nullNode;
  adj[Y5][3] = &yellow4;
  adj[Y5][4] = &nullNode;
  adj[Y5][5] = &nullNode;
  adj[Y5][6] = &blue5;
  adj[Y5][7] = &greyBox;
  
  adj[M][0] = &nullNode;
  adj[M][1] = &nullNode;
  adj[M][2] = &nullNode;
  adj[M][3] = &nullNode;
  adj[M][4] = &nullNode;
  adj[M][5] = &nullNode;
  adj[M][6] = &magenta1;
  adj[M][7] = &nullNode;
  
  adj[M1][0] = &cyan1;
  adj[M1][1] = &nullNode;
  adj[M1][2] = &magentaBox;
  adj[M1][3] = &nullNode;
  adj[M1][4] = &yellow1;
  adj[M1][5] = &nullNode;
  adj[M1][6] = &magenta2;
  adj[M1][7] = &nullNode;
  
  adj[M2][0] = &cyan2;
  adj[M2][1] = &nullNode;
  adj[M2][2] = &magenta1;
  adj[M2][3] = &nullNode;
  adj[M2][4] = &yellow2;
  adj[M2][5] = &nullNode;
  adj[M2][6] = &magenta3;
  adj[M2][7] = &nullNode;
  
  adj[M3][0] = &cyan3;
  adj[M3][1] = &nullNode;
  adj[M3][2] = &magenta2;
  adj[M3][3] = &nullNode;
  adj[M3][4] = &yellow3;
  adj[M3][5] = &nullNode;
  adj[M3][6] = &magenta4;
  adj[M3][7] = &nullNode;
  
  adj[M4][0] = &cyan4;
  adj[M4][1] = &nullNode;
  adj[M4][2] = &magenta3;
  adj[M4][3] = &nullNode;
  adj[M4][4] = &yellow4;
  adj[M4][5] = &nullNode;
  adj[M4][6] = &magenta5;
  adj[M4][7] = &nullNode;
  
  adj[M5][0] = &cyan5;
  adj[M5][1] = &nullNode;
  adj[M5][2] = &magenta4;
  adj[M5][3] = &nullNode;
  adj[M5][4] = &yellow5;
  adj[M5][5] = &nullNode;
  adj[M5][6] = &greyBox;
  adj[M5][7] = &nullNode;
  
  adj[C][0] = &nullNode;
  adj[C][1] = &nullNode;
  adj[C][2] = &nullNode;
  adj[C][3] = &nullNode;
  adj[C][4] = &nullNode;
  adj[C][5] = &cyan1;
  adj[C][6] = &nullNode;
  adj[C][7] = &nullNode;
  
  adj[C1][0] = &nullNode;
  adj[C1][1] = &cyanBox;
  adj[C1][2] = &nullNode;
  adj[C1][3] = &nullNode;
  adj[C1][4] = &magenta1;
  adj[C1][5] = &cyan2;
  adj[C1][6] = &red1;
  adj[C1][7] = &nullNode;
  
  adj[C2][0] = &nullNode;
  adj[C2][1] = &cyan1;
  adj[C2][2] = &nullNode;
  adj[C2][3] = &nullNode;
  adj[C2][4] = &magenta2;
  adj[C2][5] = &cyan3;
  adj[C2][6] = &red2;
  adj[C2][7] = &nullNode;
  
  adj[C3][0] = &nullNode;
  adj[C3][1] = &cyan2;
  adj[C3][2] = &nullNode;
  adj[C3][3] = &nullNode;
  adj[C3][4] = &magenta3;
  adj[C3][5] = &cyan4;
  adj[C3][6] = &red3;
  adj[C3][7] = &nullNode;
  
  adj[C4][0] = &nullNode;
  adj[C4][1] = &cyan3;
  adj[C4][2] = &nullNode;
  adj[C4][3] = &nullNode;
  adj[C4][4] = &magenta4;
  adj[C4][5] = &cyan5;
  adj[C4][6] = &red4;
  adj[C4][7] = &nullNode;
  
  adj[C5][0] = &nullNode;
  adj[C5][1] = &cyan4;
  adj[C5][2] = &nullNode;
  adj[C5][3] = &nullNode;
  adj[C5][4] = &magenta5;
  adj[C5][5] = &greyBox;
  adj[C5][6] = &red5;
  adj[C5][7] = &nullNode;
  
  adj[X][0] = &nullNode;
  adj[X][1] = &cyan5;
  adj[X][2] = &magenta5;
  adj[X][3] = &yellow5;
  adj[X][4] = &nullNode;
  adj[X][5] = &blue5;
  adj[X][6] = &green5;
  adj[X][7] = &red5;
  
  //Serial.println("Graph Test - array created bf init");
  //delay(500);

  //Red
	iterator[0] = &redBox;
	iterator[1] = &red1;
	iterator[2] = &red2;
	iterator[3] = &red3;
	iterator[4] = &red4;
	iterator[5] = &red5;

	//Green
	iterator[6] = &greenBox;
	iterator[7] = &green1;
	iterator[8] = &green2;
	iterator[9] = &green3;
	iterator[10] = &green4;
	iterator[11] = &green5;

	//Blue
	iterator[12] = &blueBox;
	iterator[13] = &blue1;
	iterator[14] = &blue2;
	iterator[15] = &blue3;
	iterator[16] = &blue4;
	iterator[17] = &blue5;

	//Yellows:
	iterator[18] = &yellowBox;
	iterator[19] = &yellow1;
	iterator[20] = &yellow2;
	iterator[21] = &yellow3;
	iterator[22] = &yellow4;
	iterator[23] = &yellow5;

	//Magentas:
	iterator[24] = &magentaBox;
	iterator[25] = &magenta1;
	iterator[26] = &magenta2;
	iterator[27] = &magenta3;
	iterator[28] = &magenta4;
	iterator[29] = &magenta5;

	//Cyans:
	iterator[30] = &cyanBox;
	iterator[31] = &cyan1;
	iterator[32] = &cyan2;
	iterator[33] = &cyan3;
	iterator[34] = &cyan4;
	iterator[35] = &cyan5;

	//Greys:
	iterator[36] = &greyBox;

  //Serial.println("Graph Test - end of bf init\n");
  //delay(500);
}


void Graph::printSerial() {
  int r = 0;
  int c = 0;

  Node * current;
  
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
      current = adj[r][c]; //test adj
      Serial.print("[");
      Serial.print(current->toString());
      if (current->getMapColor() == red) {
        Serial.print("]   \t\t");
      }else {
        Serial.print("]\t\t");
      }
      delay(20);
    }
    Serial.print("\n");
  }
}


/* TESTS */

/* Graph Traversal Test
 * call in loop or setup or wherever, it will halt program at end of test
 * Spirals to center of map through all nodes, prints each node
 * Tests on this graph object
 */
void Graph::graphTest() {
  
  Serial.println("Graph Test - inside graph test\n");
  delay(1000);

  printSerial();
  
  Node *endNode = getNode(Name::X); //so we're ending in the center
  Serial.print("end node: ");
  Serial.println(endNode->toString());
  delay(500);

  int loopPath[7] = {0, 0, 2, 4, 4, 7, 6};
  int numPathDirs = 7;
  int nextDir = 0;

  setCurrentNode(getNode(Name::Bl1));
  setCurrentDirection(0);
  Node *nextNode;
  
  for(int i=0; getCurrentNode()->getName() != endNode->getName(); i++) {
    Serial.print("Current Node: ");

    //Remove all print statements in this file except this one for gui test
    Serial.println(getCurrentNode()->toString());    

    /*if(currentNode->getName() != expectedNames[i]){
      Serial.println("Graph traversal test failed on step %d, node: %s and actual %s\n", i, currentNode->getName());
    }*/

    if(getCurrentNode()->isNull()){
      Serial.println("Hit an empty node");
      break;
    } 
    else {
      nextDir = loopPath[i % numPathDirs];
      setCurrentDirection(nextDir);
      nextNode = getNeighbor(getCurrentNode(), nextDir);
      setCurrentNode(nextNode);
  
      Serial.print("Moved in direction: ");
      Serial.println(getCurrentDirection());
    }
    
    delay(500);
  }
  
  Serial.print("Final Node: ");
  Serial.println(getCurrentNode()->toString()); 

  while(1);
}


/* NOTICE: we aren't using this yet, if you are looking for the function that just easily prints over serial check printRawGraph 
 * this string is really long and unfriendly to our memory so we might not use this at all
 * Iterates through every node and creates a string describing the map's current state such that
    - Nodes are '/' delimited
    - per-node information is formatted as described in Node::toString()  
    - returns a char*         
*/
char* Graph::toString() {
  char result[370];
  for(int i=0; i < NUMBER_OF_NODES; i++) {
    strcat(result, iterator[i]->toString());
    if(i != NUMBER_OF_NODES) {
      strcat(result, "/");     // nodes will be '/' delimited
    }
  }
 return result;
}

