#include "Node.h"
#include <String.h>
#include <Arduino.h>

Node::Node() {
	visited = false;
	isNullNode = false;
  tokenColor = unknown;
}

Node::Node(Name n, Color mc) {
  visited = false;
  isNullNode = false;
  tokenColor = unknown;
  
  mapColor = mc;  
	setName(n);
}

Name Node::getName() {
	return name;
}

void Node::setName(Name n) {
	name = n;
  depth = (name == X)? 5 : name % 6;  // see the Name enum to understand the relationship between depth and 'index' in Name enum (actually the integer value the name represents)
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

static char* nameTable[37] = {"Red B", "Red 1", "Red 2", "Red 3", "Red 4", "Red 5",
                          "Green B", "Green 1", "Green 2", "Green 3", "Green 4", "Green 5",
                "Blue B", "Blue 1", "Blue 2", "Blue 3", "Blue 4", "Blue 5",
                "Yellow B", "Yellow 1", "Yellow 2", "Yellow 3", "Yellow 4", "Yellow 5",
                "Magenta B", "Magenta 1", "Magenta 2", "Magenta 3", "Magenta 4", "Magenta 5",
                "Cyan B", "Cyan 1", "Cyan 2", "Cyan 3", "Cyan 4", "Cyan 5",
                "Grey B"};

static char* colorTable[8] = {"red", "green", "blue", "yellow", "magenta", "cyan", "grey", "unknown"};


//"[R1 v:true t:G]"
//<name:visited:tokenColor>
char* Node::toString() {
	char s[40] = "";

  if (isNull()) {
    strcat(s, nameToString());
  }
  else {
	  strcat(s, nameToString());
    strcat(s, ":");
    strcat(s, (visited? "t" : "f"));
    strcat(s, ":");
    strcat(s, colorToChar(tokenColor));
  }

	return s;
}

void Node::setAsNull() {
	isNullNode = true;
}

bool Node::isNull() {
	return isNullNode;
}


char * Node::colorToChar(Color c) {
	char * s = " ";
	switch(c) {
		case red: 		s = "R"; break;
		case green: 	s = "G"; break;
		case blue: 		s = "B"; break;
		case yellow: 	s = "Y"; break;
		case magenta:	s = "M"; break;
		case cyan: 		s = "C"; break;
		case grey: 		s = "X"; break;
    case unknown: s = "U"; break;
		default: 			break;
	}
	return s;
}

//TODO
char* Node::nameToString() {
  if (isNull()) {
    return "empty node";
  }
	return nameTable[name];
}

