#include <string.h>

#ifndef NODE_H
#define NODE_H
//base class

enum Color {red, green, blue, yellow, magenta, cyan, grey, unknown};

enum Name { R, R1, R2, R3, R4, R5,
			G, G1, G2, G3, G4, G5,
			Bl, Bl1, Bl2, Bl3, Bl4, Bl5,
			Y, Y1, Y2, Y3, Y4, Y5,
			M, M1, M2, M3, M4, M5,
			C, C1, C2, C3, C4, C5,
			X};	//'X' is grey cuz it's the 'crossroads'

class Node
{
	public:

		Node();
    Node(Name n, Color mc);
		Name getName();
		void setName(Name n);
		bool getVisited();
		void setVisited(bool visit);
		Color getMapColor();

		char* toString();

		void setAsNull();
		bool isNull();

    char* nameToString();
    char* colorToChar(Color c);

    int getDepth();
    
	protected:

		Name name;
		Color mapColor;
		int depth;

		Color tokenColor;
		bool visited;
		Node* adjList;

		bool isNullNode;




};

#endif
