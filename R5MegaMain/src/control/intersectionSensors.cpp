#include "intersectionSensors.h"
#include "Node.h"

intersectionSensors::intersectionSensors(Graph * mapGraph, int l0pin, int l1pin, int l2pin, int r0pin, int r1pin, int r2pin) {
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

    //dataRedBox = new pointlineData[8];
}

pointlineData intersectionSensors::getData() {
  pointlineData data;
  data.l0 = l0->getValue();
  data.l1 = l1->getValue();
  data.l2 = l2->getValue();
  data.r0 = r0->getValue();
  data.r1 = r1->getValue();
  data.r2 = r2->getValue();
  return data;
}

pointlineData intersectionSensors::getDataOverTime(long waitTimeMs) {
  long endT = millis() + waitTimeMs;
  pointlineData data;

  while(millis() < endT) {
    data.l0 |= l0->getValue();
    data.l1 |= l1->getValue();
    data.l2 |= l2->getValue();
    data.r0 |= r0->getValue();
    data.r1 |= r1->getValue();
    data.r2 |= r2->getValue();
  }
 
  return data;
}

pointlineData intersectionSensors::getDataOverTimeRolling(long waitTimeMs) {
  long t = millis();
  pointlineData data = getData();

  data.l0 = t < (pointlineTimers[0] = (data.l0 == 1)?(t + waitTimeMs):(pointlineTimers[0] ));
  data.l1 = t < (pointlineTimers[1] = (data.l1 == 1)?(t + waitTimeMs):(pointlineTimers[1]));
  data.l2 = t < (pointlineTimers[2] = (data.l2 == 1)?(t + waitTimeMs):(pointlineTimers[2]));
  data.r0 = t < (pointlineTimers[3] = (data.r0 == 1)?(t + waitTimeMs):(pointlineTimers[3]));
  data.r1 = t < (pointlineTimers[4] = (data.r1 == 1)?(t + waitTimeMs):(pointlineTimers[4]));
  data.r2 = t < (pointlineTimers[5] = (data.r2 == 1)?(t + waitTimeMs):(pointlineTimers[5]));

  return data;
}

pointlineData intersectionSensors::getNextIntersection() {
  Node *neighbor = map->getNextIntersection();
  Color intersectionType = neighbor->getMapColor();
  //pointlineData nextData;
  Serial.println(String(neighbor->toString()));

  //if( neighbor->getName() % 6 == 0 )
    //nextData = getPointLineForBox(intersectionType);
  //else
  return getPointlineFor(intersectionType, map->getCurrentDirection());
  //return nextData;
}

//for turn in place
pointlineData intersectionSensors::getTurn45Intersection(int steps) {
  Node *current = map->getCurrentNode();
  Color intersectionType = current->getMapColor();
  return getPointlineFor(intersectionType, map->getCurrentDirection() + steps);
}

//turn to a specific direction
pointlineData intersectionSensors::getTurnToIntersection(int dir) {
  Node *current = map->getCurrentNode();
  Color intersectionType = current->getMapColor();
  return getPointlineFor(intersectionType, dir);
}

pointlineData intersectionSensors::getPointlineFor(Color intersectionType, int dir) {
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

/*
pointlineData intersectionSensors::getPointlineForBox(Color intersectionType) {
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
}*/

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

char * intersectionSensors::PLDatatoString(pointlineData data) {
  char s[100] = "";
  strcat(s, data.l0?"[l0:1]":"[l0:0]");
  strcat(s, data.l1?"[l1:1]":"[l1:0]");
  strcat(s, data.l2?"[l2:1]":"[l2:0]");
  strcat(s, data.r0?"[r0:1]":"[r0:0]");
  strcat(s, data.r1?"[r1:1]":"[r1:0]");
  strcat(s, data.r2?"[r2:1]":"[r2:0]");
  return s;
}

void intersectionSensors::printDataRedNorth() {
  for(int i = 0; i<8; i++)
  {
    Serial.print(dataRedNorth[i].l0);
    Serial.print(dataRedNorth[i].l1);
    Serial.print(dataRedNorth[i].l2);
    Serial.print(dataRedNorth[i].r0);
    Serial.print(dataRedNorth[i].r1);
    Serial.print(dataRedNorth[i].r2);
    Serial.println();
  }
}
