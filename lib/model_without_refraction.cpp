#include "model_without_refraction.h"

double ModelWithoutRefraction::calculate_d(double psi_d, double psi_g,
                                           void* opaque) {
  double d = Re * (psi_d - psi_g);
  return d;
}

double ModelWithoutRefraction::calculate_psi_d(const Input& data,
                                               void* opaque) {
  if (data.R == 0) return 0;  // if target and radar in same dote
  double cos_90_psi_d =
      (data.R * data.R + data.ha * data.ha + 2 * data.ha * Re -
       data.hs * data.hs - 2 * data.hs * Re) /
      (2 * data.R * (Re + data.ha));
  double psi_d = M_PI / 2 - acos(cos_90_psi_d);
  return psi_d;
}

double ModelWithoutRefraction::calculate_psi_g(const Input& data,
                                               void* opaque) {
  if (data.R == 0) return 0;  // if target and radar in same dote
  double cos_90_psi_g =
      (data.R * data.R - data.ha * data.ha - 2 * data.ha * Re +
       data.hs * data.hs + 2 * data.hs * Re) /
      (2 * data.R * (Re + data.hs));
  double psi_g = acos(cos_90_psi_g) - M_PI / 2;
  return psi_g;
}

double ModelWithoutRefraction::calculate_phi_e(double psi_d, double psi_g,
                                               void* opaque) {
  double phi_e = psi_d - psi_g;
  return phi_e;
}

RefractionModel::Answer ModelWithoutRefraction::calculate(const Input& data,
                                                          void* opaque) {
  double psi_d = calculate_psi_d(data);
  double psi_g = calculate_psi_g(data);
  return Answer(
      {.psi_d = psi_d, .psi_g = psi_g, .d = calculate_d(psi_d, psi_g)});
}
