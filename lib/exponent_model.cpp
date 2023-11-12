#include "exponent_model.h"

double ExponentAtmosphericModel::N(double h) {
  if (h < 3000.0) {
    double dN = -0.00732 * exp(0.005577 * Ns);
    double He = 1000 / log(Ns / (Ns + 1000 * dN));
    double N = Ns * exp(-(h - hs) / He);
    return N;
  }
  if (h < 10000.0) {
    hb = 9144;
    Nb = 102.9;
  }
  double N = Ns * exp(-(h - hs) / get_Hb());
  return N;
}

double ExponentAtmosphericModel::get_Hb() {
  double Hb = (hb - hs) / log(Ns / Nb);
  return Hb;
}

double ExponentAtmosphericModel::get_Ns() { return Ns; }
