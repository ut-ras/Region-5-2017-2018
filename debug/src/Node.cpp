#include "../inc/Node.h"

Node::Node(Name n, Color mc) {
	name = n;
	visited = false;
	mapColor = mc;
}

Name Node::getName() {
	return name;
}

bool Node::getVisited() {
	return visited;
}

void Node::setVisited(bool visit) {
	visited = visit;
}

Color Node::getMapColor() {
	return mapColor;
}

/* Builds a string describing current state of the Node such that
    - fields will be comma delimited
    - field labels and values will be separated by a colon
*/
string Node::toString() {
	// index into the name lookup table with the name enum
	string name = nameTable[this.name];
	string visited = ((this.visited) ? "true" : "false");
	return "Name:" + name + ",Visited:" + visited;			// fields will be comma delimited, labels and values will be separated by colons 
	// expand this as we track more for the nodes ***
}
