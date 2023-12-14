#include "exponent_model.h"

double ExponentAtmosphericModel::N(double h) {
  double hb = 12192;
  double Nb = 66.65;
  if (h < 10000.0) {
    hb = 9144;
    Nb = 102.9;
  }
  double N = Ns * exp(-(h - hs) / get_Hb());
  return N;
}

double ExponentAtmosphericModel::get_Hb() {
  double hb = 12192;
  double Nb = 66.65;
  double Hb = (hb - hs) / log(Ns / Nb);
  return Hb;
}

double ExponentAtmosphericModel::get_Ns() { return Ns; }
