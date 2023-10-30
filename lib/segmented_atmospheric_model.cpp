#include "segmented_atmosheric_model.h"

double SegmentedAtmosphericModel::N(double h) {
  double N1 = get_N1();
  double H = get_H();
  double dN = get_dN();
  if (h >= hs && h <= hs + 1000) {
    return Ns + (h - hs) * dN;
  }
  if (h >= hs + 1000 && h <= 9000) {
    return N1 * exp(-(h - hs - 1000) / H);
  }
  if (h > 9000) {
    return 105 * exp(-(h - 9000) / 7023);
  }
}

double SegmentedAtmosphericModel::get_N1() {
  return Ns + (1000 - hs) * get_dN();
}

double SegmentedAtmosphericModel::get_dN() {
  return -0.00732 * exp(0.005577 * Ns);
}

double SegmentedAtmosphericModel::get_H() {
  return (8000 - hs) / std::log(get_N1() / 105);
}
