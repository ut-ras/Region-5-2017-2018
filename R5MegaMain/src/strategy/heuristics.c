/*
 *  heuristics.h
 *
 *  File containing heuristics; implements part of this algorithm:
 *  https://www.sharelatex.com/read/zqghcfgkmpvc
 */

#include "heuristics.h"

// ----------Distance function----------
// Distance function to use on the heuristic.
// Currently uses l_1 (taxicab) distance.
// Parameters:
//      Node firstNode : first input node
//      Node secondNode : second input node
// Returns:
//      float : computed distance
float distance(Node firstNode, Node secondNode) {
    return(
        abs(firstNode.x - secondNode.x) +
        abs(firstNode.y - secondNode.y));
}


// ----------heuristic-----------
// Compute the heuristic value of a given node.
// Parameters:
//      Node x : input node
//      float t : time remaining, in seconds
//      tokens : expected number of tokens
// Returns:
//      float : computed heuristic value
const Node homeNodes[8] = {list of home nodes};
const Node homeBox; // Home node
float heuristic(Node x, float t, float tokens[8]) {

    float value = 0;
    for(uint8_t i = 0; i < 8; i++) {
        value += tokens[i] / distance(x, homeNodes[i]);
    }
    value *= pow(t, ALPHA);
    value += BETA / (pow(t, LAMBDA) * distance(x, homeBox));
    return(value);
}

