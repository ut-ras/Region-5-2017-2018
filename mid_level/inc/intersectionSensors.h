#include "../../drivers/inc/pointline.h"

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

  intersectionSensors(int _l0pin, int _l1pin, int _l2pin, int _r0pin, int _r1pin, int _r2pin);
  pointlineData getData();
  pointlineData getNextIntersection();  //based on current location and direction in map

private:
  pointline l0;
  pointline l1;
  pointline l2;
  pointline r0;
  pointline r1;
  pointline r2;
};
