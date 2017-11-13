#include "../inc/Node.h"


Node::Node(Name n) 
{
	name = n;
	visited = false;
}

Name Node::getName() 
{
	return name;
}

bool Node::getVisited() 
{
	return visited;
}

void Node::setVisited(bool visit) 
{
	visited = visit; 
}