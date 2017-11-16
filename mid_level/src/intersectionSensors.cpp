#include "../inc/intersectionSensors.h"

intersectionSensors::intersectionSensors(Graph mapGraph, int l0pin, int l1pin, int l2pin, int r0pin, int r1pin, int r2pin) {
    l0 = new pointline(l0pin);
    l1 = new pointline(l1pin);
    l2 = new pointline(l2pin);
    r0 = new pointline(r0pin);
    r1 = new pointline(r1pin);
    r2 = new pointline(r2pin);
    map = mapGraph;
}

pointlineData intersectionSensors::getData() {
  pointlineData data;
  data.l0 = l0.getValue();
  data.l1 = l1.getValue();
  data.l2 = l2.getValue();
  data.r0 = r0.getValue();
  data.r1 = r1.getValue();
  data.r2 = r2.getValue();
  return data;
}

pointlineData intersectionSensors::getNextIntersection() {
  Node currentNode = map.getCurrentNode();
	int dir = map.getCurrentDirection();
  Node neighbor = map.getNeighbor();
  Node::Color intersectionType = neighbor.getMapColor();
  return getPointlineFor(intersectionType, dir);
}

pointlineData intersectionSensors::getPointlineFor(Node::Color c, int dir) {
  if ((intersectionType == Node::Color.red) || (intersectionType == Node::Color.cyan) || (intersectionType == Node::Color.yellow) || (intersectionType == Node::Color.blue)) {
    pointlineData[8] data = new pointlineData[8];
    data[0] = createPointlineData(1, 0, 0, 0, 1, 1);
    data[1] = createPointlineData(0, 1, 0, 1, 1, 1);
    data[2] = createPointlineData(0, 0, 1, 1, 1, 0);
    data[3] = createPointlineData(1, 0, 0, 1, 0, 0);
    data[4] = createPointlineData(1, 1, 0, 0, 0, 1);
    data[5] = createPointlineData(1, 1, 1, 0, 1, 0);
    data[6] = createPointlineData(0, 1, 1, 1, 0, 0);
    data[7] = createPointlineData(0, 0, 1, 0, 0, 1);

    switch(intersectionType) {
      case Node::Color.cyan:
        offset = -2; break;
      case Node::Color.yellow:
        offset = -4; break;
      case Node::Color.blue:
        offset = -6; break;
    }
    index = dir + offset;
    index = (index >= 0) ? (index) : (8 + index);   //shift for different colors
    return data[index];
  }
  else if ((intersectionType == Node::Color.magenta) || (intersectionType == Node::Color.green)) {

  }
  else if (intersectionType == Node::Color.grey) {

  }
  //also need something for drop off zones
}

pointlineData intersectionSensors::createPointlineData(int l0, int l1, int l2, int r0, int r1, int r2) {
  pointlineData d;
  d.l0 = l0;
  d.l1 = l1;
  d.l2 = l2;
  d.r0 = r0;
  d.r1 = r1;
  d.r2 = r2;
  return d;
}
