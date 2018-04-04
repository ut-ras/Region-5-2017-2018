/*
 *  heuristics.h
 *
 *  File containing heuristics; implements part of this algorithm:
 *  https://www.sharelatex.com/read/zqghcfgkmpvc
 */

#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "../Node.h"
#include "../Graph.h"

// ----------Tuning coefficients----------

// Robot speed
#define SPEED 1
// Time influence characteristic
#define ALPHA 1
// Return to white box coefficient
#define BETA 1
// Return to white box characteristic
#define LAMBDA 1
// Distance function
float distance(Node *firstNode, Node *secondNode);


// ----------heuristic-----------
// Compute the heuristic value of a given node.
// Parameters:
//      Node *x : input node
//      float t : time remaining, in seconds
//      tokens : expected number of tokens
// Returns:
//      float : computed heuristic value
float heuristic(Node *x, float t, float tokens[8]);


#endif
