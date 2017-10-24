#include "../inc/intersectionSensors.h"

intersectionSensors::intersectionSensors(int l0pin, int l1pin, int l2pin, int r0pin, int r1pin, int r2pin) {
    l0 = new pointline(l0pin);
    l1 = new pointline(l1pin);
    l2 = new pointline(l2pin);
    r0 = new pointline(r0pin);
    r1 = new pointline(r1pin);
    r2 = new pointline(r2pin);

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
