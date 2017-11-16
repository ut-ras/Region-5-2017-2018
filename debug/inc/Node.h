#include<string>


//base class
class Node
{
protected:
	Name name;
	Color mapColor;
	Color tokenColor;
	bool visited;
	Node* adjList;

public:
	enum Color {red, green, blue, yellow, magenta, cyan, grey};
	enum Name {R, R1, R2, R3, R4, G, G1, G2, G3, G4, B, B1, B2, B3, B4, Y, Y1, Y2, Y3, Y4, M, M1, M2, M3, M4, C, C1, C2, C3, C4, X};	//'X' is grey cuz it's the 'crossroads'

	Node(Name n, Color mc);
	Name getName();
	bool getVisited();
	void setVisited(bool visit);
	Color getMapColor();
};
