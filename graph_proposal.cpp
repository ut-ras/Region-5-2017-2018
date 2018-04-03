/*
 *	Proposed code to replace Graph.cpp.
 */


#include <stdint.h>


// ----------vector----------
// Get the 45-degree-aligned angle of a vector in Z2.
// The vector is defined as an equivalence class Z/8Z, with 0 at due north
// and subsequent angles moving in 45 degree increments clockwise.
// Parameters:
//		int8_t x : x coordinate
//		int8_t y : y coordinate
// Returns:
//		uint8_t : vector number, as defined above
const uint8_t vectorTable[8] = {5, 6, 7, 4, 0, 0, 3, 2, 1}
uint8_t vector(int8_t x, int8_t y) {

	// Normalize vectors
	if(x != 0) {
		x = x / abs(x);
	}
	if(y != 0) {
		y = y / abs(y);
	}

	// vectorTable is indexed by (x+1) + 3(y+1)
	return(vectorTable[(x + 1) + 3 * (y + 1)])
}

// ----------getAdjacency----------
// Get the adjacency of a point (x,y) in 45 degree increments.
// Parameters:
//		int8_t x : x coordinate
//		int8_t y : y coordinate
// Returns:
//		uint8_t : packed adjacency list. Bit n indicates whether the point
//			has a connection at vector n.
uint8_t getAdjacency(int8_t x, int8_t y) {

	// Center point is fully connected
	if(x == 0 && y == 0) {
		return(0xFF);
	}	

	// Outer-most points
	if(x == 6 || y == 6) {
		return(0x01 << vector(x, y));
	}

	// Remaining points
	else {
		// Even vectors (0,2,4,6) are 90-degree aligned
		if(vector(x,y) % 2 == 0) {
			return(0x55);
		}
		// Odd vectors return the vector, the opposite,
		// and the two vectors adjacent to the opposite.
		else {
			return(
				(0x01 << vector(x, y)) |
				(0x01 << ((vector(x,y) + 3) % 8)) |
				(0x01 << ((vector(x,y) + 4) % 8)) |
				(0x01 << ((vector(x,y) + 5) % 8))
			);
		}
	}
}
