/*
 *  recursion.h
 *
 *  Implements the recursion described in the algorithm:
 *  https://www.sharelatex.com/read/zqghcfgkmpvc
 */

#include "recursion.h"


// ----------utility----------
// Compute the utility of a node recursively.
// Parameters:
//		Node *referenceNode : node to calculate the value of
//		float time : time remaining
//		float tokens[8] : a list of tokens currently in the robot
//		float remainingTokens[8] : list of tokens that haven't been picked up yet
//		uint8_t layer : layer remaining.
//			Each recursive call subtracts one from layer; when layer
//			reaches zero, the recursion is terminated and heuristic is called.
//		Graph graph : graph class containing graph data
// Returns:
// 		float : utility of the given node
float utility(
	Node *referenceNode, float time,
	float tokens[8], float remainingTokens[8],
	uint8_t layer, Graph *graph) {

	// Check for recursion limit
	if(layer == 0) {
		return(heuristic(referenceNode, time));
	}

	// Memory for current highest node
	uint8_t highestIndex;
	float highestUtility;
	// Arrays for creating expected token and remaining arrays
	float expectedTokens[8];
	float expectedRemaining[8];
	// Scan each direction
	for(uint8_t i = 0; i < 8; i++) {

		if(Graph->getNeighbor(referenceNode))

	}

/*
	pseudocode:

	for each node:
		update the expected token values for that node
		call utility on that node with tokens
		compare to the previous stored node
		discard if less utility

	return the maximal utility
*/
	return;

}