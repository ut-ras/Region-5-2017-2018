using namespace std;

int main(){
	Graph g = new Graph();
	g.setCurrentNode(g.getNode(Node::Name::Y));
	g.setCurrentDirection(1);
	cout << "Current Node is: " <<g.getCurrentNode() << "\nCurrent Direction is: " << g.getCurrentDirection();
}