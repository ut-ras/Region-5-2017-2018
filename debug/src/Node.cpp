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
