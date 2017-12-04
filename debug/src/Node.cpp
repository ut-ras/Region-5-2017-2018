#include "../inc/Node.h"

Node::Node() {
	visited = false;
}

Node::Node(Name n, Color mc) {
	name = n;
	visited = false;
	mapColor = mc;
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

//"[R1 v:true t:G]"
String Node::toString() {
	String s = "[" + nameToString();
	s += "v:" + visited;
	if (visited) {
		s += " t:" + colorToChar(tokenColor);
	}
	s += "]"
	return s;
}

char Node::colorToChar(Color c) {
	char s = '';
	switch(c) {
		case red: 		s = "R"; break;
		case green: 	s = "G"; break;
		case blue: 		s = "B"; break;
		case yellow: 	s = "Y"; break;
		case magenta: s = "M"; break;
		case cyan: 		s = "C"; break;
		case grey: 		s = "X"; break;
		default: 			break;
	}
	return s;
}

String Node::nameToString() {
	return "" + colorToChar(mapColor) + depth;
}
