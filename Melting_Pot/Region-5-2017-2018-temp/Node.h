//#include <string>


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
		Node(int n, int mc, int d); //n = Name, mc = Color
		int getName();
		void setName(int n); //n = Name
		bool getVisited();
		void setVisited(bool visit);
		int getMapColor();

		String toString();

	protected:

		Name name;
		Color mapColor;
		int depth;

		Color tokenColor;
		bool visited;
		Node* adjList;
		String nameTable[37] = {"Red Box", "Red 1", "Red 2", "Red 3", "Red 4", "Red 5",
		                      "Green Box", "Green 1", "Green 2", "Green 3", "Green 4", "Green 5",
							  "Blue Box", "Blue 1", "Blue 2", "Blue 3", "Blue 4", "Blue 5",
							  "Yellow Box", "Yellow 1", "Yellow 2", "Yellow 3", "Yellow 4", "Yellow 5",
							  "Magenta Box", "Magenta 1", "Magenta 2", "Magenta 3", "Magenta 4", "Magenta 5",
							  "Cyan Box", "Cyan 1", "Cyan 2", "Cyan 3", "Cyan 4", "Cyan 5",
							  "Grey Box"};

	    String colorTable[8] = {"red", "green", "blue", "yellow", "magenta", "cyan", "grey", "unknown"};



	/* Use the lookup  tables for these values
	char colorToChar(Color c);
	String nameToString();
	*/




};
