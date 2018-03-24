#include "intersectionSensors.h"
#include "Node.h"
intersectionSensors::intersectionSensors(Graph mapGraph, int l0pin, int l1pin, int l2pin, int r0pin, int r1pin, int r2pin) {
    l0 = new pointline(l0pin);
    l1 = new pointline(l1pin);
    l2 = new pointline(l2pin);
    r0 = new pointline(r0pin);
    r1 = new pointline(r1pin);
    r2 = new pointline(r2pin);
    map = mapGraph;

    dataRedNorth = new pointlineData[8];
    dataRedNorth[0] = createPointlineData(1, 0, 0, 0, 1, 1);
    dataRedNorth[1] = createPointlineData(0, 1, 0, 1, 1, 1);
    dataRedNorth[2] = createPointlineData(0, 0, 1, 1, 1, 0);
    dataRedNorth[3] = createPointlineData(1, 0, 0, 1, 0, 0);
    dataRedNorth[4] = createPointlineData(1, 1, 0, 0, 0, 1);
    dataRedNorth[5] = createPointlineData(1, 1, 1, 0, 1, 0);
    dataRedNorth[6] = createPointlineData(0, 1, 1, 1, 0, 0);
    dataRedNorth[7] = createPointlineData(0, 0, 1, 0, 0, 1);
}

intersectionSensors::pointlineData intersectionSensors::getData() {
  pointlineData data;
  data.l0 = l0->getValue();
  data.l1 = l1->getValue();
  data.l2 = l2->getValue();
  data.r0 = r0->getValue();
  data.r1 = r1->getValue();
  data.r2 = r2->getValue();
  return data;
}

intersectionSensors::pointlineData intersectionSensors::getNextIntersection() {
  Node *currentNode = map.getCurrentNode();
	int dir = map.getCurrentDirection();
  Node *neighbor = map.getNeighbor(currentNode, dir);
  intersectionType = neighbor->getMapColor();
  return getPointlineFor(intersectionType, dir);
}

intersectionSensors::pointlineData intersectionSensors::getPointlineFor(Color c, int dir) {
    int offset, index;
  if ((intersectionType == red) || (intersectionType == cyan) || (intersectionType == yellow) || (intersectionType == blue)) {
    switch(intersectionType) {
      case cyan:
        offset = -2; break;
      case yellow:
        offset = -4; break;
      case blue:
        offset = -6; break;
    }
    index = dir + offset;
    index = (index >= 0) ? (index) : (8 + index);   //shift for different colors
    return dataRedNorth[index];
  }
  else if ((intersectionType == magenta) || (intersectionType == green)) {
    if (dir % 2 == 0) {
      return createPointlineData(0, 1, 0, 0, 1, 0);
    }
    else {
      return createPointlineData(0, 0, 1, 0, 0, 1);
    }
  }

  //also need something for drop off zones
}

intersectionSensors::pointlineData intersectionSensors::createPointlineData(int l0, int l1, int l2, int r0, int r1, int r2) {
  pointlineData d;
  d.l0 = l0;
  d.l1 = l1;
  d.l2 = l2;
  d.r0 = r0;
  d.r1 = r1;
  d.r2 = r2;
  return d;
}