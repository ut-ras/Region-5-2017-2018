#include <string>


//base class
class Node
{
protected:
	Name name;
	Color mapColor;
	int depth;

	Color tokenColor;
	bool visited;
	Node* adjList;
	String[] nameTable = {"Red Box", "Red 1", "Red 2", "Red 3", "Red 4", "Red 5",
	                      "Green Box", "Green 1", "Green 2", "Green 3", "Green 4", "Green 5",
						  "Blue Box", "Blue 1", "Blue 2", "Blue 3", "Blue 4", "Blue 5",
						  "Yellow Box", "Yellow 1", "Yellow 2", "Yellow 3", "Yellow 4", "Yellow 5",
						  "Magenta Box", "Magenta 1", "Magenta 2", "Magenta 3", "Magenta 4", "Magenta 5",
						  "Cyan Box", "Cyan 1", "Cyan 2", "Cyan 3", "Cyan 4", "Cyan 5",
						  "Grey Box"};

    String[] colorTable = {"red", "green", "blue", "yellow", "magenta", "cyan", "grey", "unknown"}

public:
	enum Color {red, green, blue, yellow, magenta, cyan, grey, unknown};
	enum Name {R, R1, R2, R3, R4, R5, G, G1, G2, G3, G4, G5, B, B1, B2, B3, B4, B5, Y, Y1, Y2, Y3, Y4, Y5, M, M1, M2, M3, M4, M5, C, C1, C2, C3, C4, C5, X};	//'X' is grey cuz it's the 'crossroads'

	Node();
	Node(Name n, Color mc, int d);
	Name getName();
	void setName(Name n);
	bool getVisited();
	void setVisited(bool visit);
	Color getMapColor();

	String toString();

	/* Use the lookup  tables for these values
	char colorToChar(Color c);
	String nameToString();
	*/
};
