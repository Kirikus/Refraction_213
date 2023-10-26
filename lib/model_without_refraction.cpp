#include "model_without_refraction.h"

double ModelWithoutRefraction::calculate_d(double psi_d, double psi_g,
                                           void* opaque) {
  double d = Re * (psi_d - psi_g);
  return d;
}

double ModelWithoutRefraction::calculate_psi_d(double ha, double hs, double R,
                                               void* opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  double cos_90_psi_d =
      (R * R + ha * ha + 2 * ha * Re - hs * hs - 2 * hs * Re) /
      (2 * R * (Re + ha));
  double psi_d = M_PI / 2 - acos(cos_90_psi_d);
  return psi_d;
}

double ModelWithoutRefraction::calculate_psi_g(double ha, double hs, double R,
                                               void* opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  double cos_90_psi_g =
      (R * R - ha * ha - 2 * ha * Re + hs * hs + 2 * hs * Re) /
      (2 * R * (Re + hs));
  double psi_g = acos(cos_90_psi_g) - M_PI / 2;
  return psi_g;
}

double ModelWithoutRefraction::calculate_phi_e(double psi_d, double psi_g,
                                               void* opaque) {
  double phi_e = psi_d - psi_g;
  return phi_e;
}

Answer ModelWithoutRefraction::calculate(double ha, double hs, double R,
                                         void* opaque) {
  psi_d = calculate_psi_d(ha, hs, R);
  psi_g = calculate_psi_g(ha, hs, R);
  d = calculate_d(psi_d, psi_g);
  return Answer(psi_d, psi_g, d);
}
