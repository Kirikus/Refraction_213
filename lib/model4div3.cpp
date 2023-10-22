#include "model4div3.h"

double Model4div3::calculate_d(double psi_d, double psi_g, void *opaque) {
  double hs = *(reinterpret_cast<double *>(opaque));
  double d = (k() * Re + hs) * calculate_phi_e(psi_d, psi_g);
  return d;
}

double Model4div3::calculate_psi_d(double ha, double hs, double R,
                                   void *opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  double sin_psi_d = (ha - hs) / R * (1 - (ha - hs) / 2 / (k() * Re + ha)) +
                     R / 2 / (k() * Re + ha);
  double psi_d = std::asin(sin_psi_d);
  return psi_d;
}

double Model4div3::calculate_psi_g(double ha, double hs, double R,
                                   void *opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  double sin_psi_g = (ha - hs) / R * (1 + (ha - hs) / 2 / (k() * Re + ha)) -
                     R / 2 / (k() * Re + ha);
  double psi_g = std::asin(sin_psi_g);
  return psi_g;
}

double Model4div3::calculate_phi_e(double psi_d, double psi_g, void *opaque) {
  double phi_e = psi_d - psi_g;
  return phi_e;
}

Answer Model4div3::calculate(double ha, double hs, double R, void *opaque) {
  psi_d = calculate_psi_d(ha, hs, R);
  psi_g = calculate_psi_g(ha, hs, R);
  d = calculate_d(psi_d, psi_g, reinterpret_cast<void *>(&hs));
  return Answer(psi_d, psi_g, d);
}

double Model4div3::k() { return 4 / 3; }
