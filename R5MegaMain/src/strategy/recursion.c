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
//		Node referenceNode : node to calculate the value of
//		float time : time remaining
//		uint8_t tokens[8] : a list of tokens currently in the robot
//		uint8_t remainingTokens[8] : list of tokens that haven't been picked up yet
//		uint8_t layer : layer remaining.
//			Each recursive call subtracts one from layer; when layer
//			reaches zero, the recursion is terminated and heuristic is called.
// Returns:
// 		float : utility of the given node
float utility(
	Node referenceNode, float time,
	uint8_t tokens[8], uint8_t remainingTokens[8],
	uint8_t layer) {

	// Check for recursion limit
	if(layer == 0) {
		return(heuristic(referenceNode, time));
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