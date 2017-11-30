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
	string[] nameTable = {"Red Box", "Red 1", "Red 2", "Red 3", "Red 4", "Green Box", "Green 1", "Green 2", "Green 3", "Green 4", "Blue Box", "Blue 1", "Blue 2", "Blue 3", "Blue 4",
						  "Yellow Box", "Yellow 1", "Yellow 2", "Yellow 3", "Yellow 4", "Magenta Box", "Magenta 1", "Magenta 2", "Magenta 3", "Magenta 4",
						  "Cyan Box", "Cyan 1", "Cyan 2", "Cyan 3", "Cyan 4", "Grey Box"}; 

public:
	enum Color {red, green, blue, yellow, magenta, cyan, grey};
	enum Name {R, R1, R2, R3, R4, G, G1, G2, G3, G4, B, B1, B2, B3, B4, Y, Y1, Y2, Y3, Y4, M, M1, M2, M3, M4, C, C1, C2, C3, C4, X};	//'X' is grey cuz it's the 'crossroads'

	Node(Name n, Color mc);
	Name getName();
	bool getVisited();
	void setVisited(bool visit);
	Color getMapColor();
	string toString();
};
