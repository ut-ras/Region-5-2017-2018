#include "Node.h"
#include <String.h>
#include <Arduino.h>

Node::Node() {
	visited = false;
	isNullNode = false;
}

Node::Node(Name n, Color mc) {
	name = n;
	visited = false;
	mapColor = mc;
	tokenColor = unknown;
	depth = (name == X)? 5 : name % 6;	// see the Name enum to understand the relationship between depth and 'index' in Name enum (actually the integer value the name represents)
}

Name Node::getName() {
	return name;
}

void Node::setName(Name n) {
	name = n;
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

static char* nameTable[37] = {"Red Box", "Red 1", "Red 2", "Red 3", "Red 4", "Red 5",
                          "Green Box", "Green 1", "Green 2", "Green 3", "Green 4", "Green 5",
                "Blue Box", "Blue 1", "Blue 2", "Blue 3", "Blue 4", "Blue 5",
                "Yellow Box", "Yellow 1", "Yellow 2", "Yellow 3", "Yellow 4", "Yellow 5",
                "Magenta Box", "Magenta 1", "Magenta 2", "Magenta 3", "Magenta 4", "Magenta 5",
                "Cyan Box", "Cyan 1", "Cyan 2", "Cyan 3", "Cyan 4", "Cyan 5",
                "Grey Box"};

static char* colorTable[8] = {"red", "green", "blue", "yellow", "magenta", "cyan", "grey", "unknown"};


//"[R1 v:true t:G]"
//<name:visited:tokenColor>
char* Node::toString() {
	char s[30];
 
  //Serial.print("Node toString - name: ");
  //Serial.println(name);
  //delay(500);
  //Serial.print("Node toString - tokenColor: ");
  //Serial.println(tokenColor);
  //delay(500);
  
	strcat(s, nameTable[name]);
	strcat(s, ":");
	strcat(s, (visited? "t" : "f"));
	strcat(s, ":");
	strcat(s, colorTable[tokenColor]);
	return s;
}

void Node::setAsNull() {
	isNullNode = true;
}

bool Node::isNull() {
	return isNullNode;
}

/*
char Node::colorToChar(Color c) {
	char s = '';
	switch(c) {
		case red: 		s = "R"; break;
		case green: 	s = "G"; break;
		case blue: 		s = "B"; break;
		case yellow: 	s = "Y"; break;
		case magenta:	s = "M"; break;
		case cyan: 		s = "C"; break;
		case grey: 		s = "X"; break;
		default: 			break;
	}
	return s;
}

String Node::nameToString() {
	return "" + colorToChar(mapColor) + depth;
}
*/
