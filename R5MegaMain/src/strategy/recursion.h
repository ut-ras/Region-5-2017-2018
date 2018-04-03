/*
 *  recursion.h
 *
 *  Implements the recursion described in the algorithm:
 *  https://www.sharelatex.com/read/zqghcfgkmpvc
 */

#ifndef RECURSION_H
#define RECURSION_H


#include "heuristics.h"
#include "../Node.h"
#include "../Graph.h"
#include <stdint.h>


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
	uint8_t layer);


#endif
