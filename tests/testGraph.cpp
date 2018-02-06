#include <stdio.h>
#include "../control/inc/Graph.h"

Graph* g;

void setupGraphTest() {
	g = new Graph();
	g.setCurrentNode(g.getNode(Node::Name::Y));
	g.setCurrentDirection(0);
}

void loopGraphTest() {

	Serial.println("Current Node is: " + g->getCurrentNode() + "\nCurrent Direction is: " + g->getCurrentDirection());
	if(g->getNeighbor(g->getCurrentNode(), 0).getName() ==  Node::Name::M)
		Serial.println("Get neighbor test 1 passed");
	else
		Serial.println("Get neighbor test 1 failed");
}
