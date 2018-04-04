#ifndef intersectionsensors_h
#define intersectionsensors_h
#include "../drivers/pointline.h"
#include "Graph.h"
#include "Node.h"

/*
 * Class that abstracts the pointline class, array of line sensors for detecting intersections of lines
 * usage: in high level code, determine the desired pointlineData for the next intersection, then move and getData until data matches
 * 0 is front
 */

typedef struct pointlineData {
  bool l0;
  bool l1;
  bool l2;
  bool r0;
  bool r1;
  bool r2;
  pointlineData& operator=(const pointlineData& a) {
      l0 = a.l0;
      l1 = a.l1;
      l2 = a.l2;
      r0 = a.r0;
      r1 = a.r1;
      r2 = a.r2;
      return *this;
  }
  bool operator==(const pointlineData& a) const {
      return ((l0 == a.l0) && (l1 == a.l1) && (l2 == a.l2) && (r0 == a.r0) && (r1 == a.r1) && (r2 == a.r2));
  }
  bool operator!=(const pointlineData& a) const {
      return !((l0 == a.l0) && (l1 == a.l1) && (l2 == a.l2) && (r0 == a.r0) && (r1 == a.r1) && (r2 == a.r2));
  }
  String toString() {
      String s = String("l0=" + String(l0?"true":"false") + " l1=" + String(l1?"true":"false") + " l2=" + String(l2?"true":"false") + "\n");
      s += String("r0=" + String(r0?"true":"false") + " r1=" + String(r1?"true":"false") + " r2=" + String(r2?"true":"false") + "\n");
      return s;
  }
} pointlineData;

class intersectionSensors {
public:
  char* PLDatatoString(pointlineData data);

  intersectionSensors(Graph * mapGraph, int l0pin, int l1pin, int l2pin, int r0pin, int r1pin, int r2pin);
  pointlineData getData();
  pointlineData getDataOverTime(long waitTimeMs);
  pointlineData getNextIntersection();  //based on current location and direction in map

  pointlineData getTurn45Intersection(int steps);  //for turn in place
  pointlineData getTurnToIntersection(int dir);  //turn to a specific direction

  pointlineData createPointlineData(int l0, int l1, int l2, int r0, int r1, int r2);

  void printDataRedNorth();

private:
  Graph * map;
  pointline *l0;
  pointline *l1;
  pointline *l2;
  pointline *r0;
  pointline *r1;
  pointline *r2;
  pointlineData *data;
  pointlineData *dataRedNorth;

  pointlineData getPointlineFor(Color intersectionType, int dir);
};
#endif
