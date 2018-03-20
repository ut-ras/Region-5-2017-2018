#ifndef intersectionsensors_h
#define intersectionsensors_h
#include "pointline.h"
#include "Graph.h"
#include "Node.h"
/*
 * Class that abstracts the pointline class, array of line sensors for detecting intersections of lines
 * TODO: add enum or something to describe [intersection type]
 * TODO: add something to describe [direction of movement]
 * TODO: add static function that converts current [direction of movement] and [intersection type]
 *       and returns the desired pointlineData for the next intersection
 * get the [intersection type] and [direction of movement] from the data logging code
 * usage: in high level code, determine the desired pointlineData for the next intersection, then move and getData until data matches
 */


class intersectionSensors {
public:

  typedef struct pointlineData {
    bool l0;
    bool l1;
    bool l2;
    bool r0;
    bool r1;
    bool r2;
  } pointlineData;

  intersectionSensors(Graph mapGraph, int l0pin, int l1pin, int l2pin, int r0pin, int r1pin, int r2pin);
  pointlineData getData();
  pointlineData getNextIntersection();  //based on current location and direction in map
  pointlineData createPointlineData(int l0, int l1, int l2, int r0, int r1, int r2);
  Color intersectionType;
private:
  Graph map;
  pointline *l0;
  pointline *l1;
  pointline *l2;
  pointline *r0;
  pointline *r1;
  pointline *r2;
  pointlineData *data;
  pointlineData *dataRedNorth;

  pointlineData getPointlineFor(Color c, int dir);
};
#endif
