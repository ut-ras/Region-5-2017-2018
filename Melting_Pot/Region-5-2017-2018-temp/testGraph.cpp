#include <stdio.h>
#include "Graph.h"
#include "Node.h"

Graph* gA;

void setupGraphTestA() {
	gA = new Graph();
	gA->setCurrentNode(gA->getNode(Name::Y));
	gA->setCurrentDirection(0);
}

void loopGraphTestA() {

	//Serial.println("Current Node is: " + g->getCurrentNode() + "\nCurrent Direction is: " + g->getCurrentDirection());
	if(gA->getNeighbor(gA->getCurrentNode(), 0)->getName() ==  Name::M) {
		//Serial.println("Get neighbor test 1 passed");
	}
	else {
		//Serial.println("Get neighbor test 1 failed");
	}
}
