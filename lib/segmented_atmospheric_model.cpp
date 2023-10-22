#include "segmented_atmosheric_model.h"

double SegmentedAtmosphericModel::N(double h) {
  set_dN();
  set_H();
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

double SegmentedAtmosphericModel::set_hs(double hs) { this->hs = hs; }

double SegmentedAtmosphericModel::set_N1(double N1) { this->N1 = N1; }

double SegmentedAtmosphericModel::set_Ns(double Ns) { this->Ns = Ns; }

void SegmentedAtmosphericModel::set_dN() {
  this->dN = -0.00732 * exp(0.005577 * Ns);
}

void SegmentedAtmosphericModel::set_H() {
  this->H = (8000 - hs) / std::log(N1 / 105);
}
