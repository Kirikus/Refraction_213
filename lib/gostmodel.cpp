#include "gostmodel.h"

#include <cmath>

double GOSTModel::Ro(double h) {
  double rh = 0.6;
  double Ro_max = 12.8;
  double Ro_0 = Ro_max * rh;
  if (h <= 2000) return Ro_0 * (1 - 0.2523 * h * 0.001);
  if (2000 < h && h <= 8000)
    return 0.4954 * Ro_0 * pow(M_E, -(h - 2000) / 1861);
  if (h > 8000) return 0.0197 * Ro_0 * exp(-(h - 8000) / 1158);
}

double GOSTModel::N(double h) {
  double T = T_via_h->y(h);
  double P = p_via_h->y(h);
  double e = T * Ro(h) / 216.68;
  return 77.6 / T * (P / 100 + 4810 * e / 100 / T);
}

