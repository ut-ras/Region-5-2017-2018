
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


void Graph::bruteForceInit() {

    
  
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

