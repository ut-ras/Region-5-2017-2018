#include<string>

enum Color {red, green, blue, yellow, magenta, cyan, grey};
enum Name {R, R1, R2, R3, R4, G, G1, G2, G3, G4, B, B1, B2, B3, B4, Y, Y1, Y2, Y3, Y4, M, M1, M2, M3, M4, C, C1, C2, C3, C4, X}	//'X' is grey cuz it's the crossroads

//base class
class Node
{
protected:
	Name name;
	bool visited;
	Node* adjList;

public:
	//getters and setters
}

//intersection node
class Intersection: public Node
{
protected:
	bool tokenFound;
	Color colorToken;
}
