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

	// Get the total number of remaining tokens
	float totalTokens = 0;
	for(int i = 0; i < 8; i++) {
		totalTokens += remainingTokens[i];
	}

	// Memory for current highest node
	uint8_t highestIndex = 0;
	float highestUtility = 0;
	// Arrays for creating expected token and remaining arrays
	float expectedTokens[8];
	float expectedRemaining[8];

	// Scan each direction
	for(uint8_t i = 0; i < 8; i++) {
		
		// Intermediate variables
		float currentUtility;
		Node *neighborNode;

		// Get target neighbor node
		neighborNode = Graph->getNeighbor(referenceNode, i);

		// Not a null node
		if(!neighborNode.isNullNode) {

			// Not visited -> increase the expected tokens
			if(!neighborNode.visited) {
				for(uint8_t i = 0; i < 8; i++) {
					expectedTokens[i] += remainingTokens[i] / totalTokens;
					expectedRemaining[i] -= remainingTokens[i] / totalTokens;
				}
			}

			// Get recursive utility
			currentUtility = utility(
				neighborNode,
				time - SPEED * distance(referenceNode, neighborNode),
				expectedTokens,
				remainingTokens,
				layer - 1,
				graph);

			// Update highest utility if applicable
			if(currentUtility > highestUtility) {
				highextIndex = i;
				highestUtility = currentUtility;
			}
		}

	}
	return(highestUtility);
}