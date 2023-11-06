#include "effective_radius_model.h"

double EffectiveRadiusModel::calculate_d(double psi_d, double psi_g,
                                         void *opaque) {
  Input data = *(reinterpret_cast<Input *>(opaque));
  double d = (k(data) * Re + data.hs) * calculate_phi_e(psi_d, psi_g);
  return d;
}

double EffectiveRadiusModel::calculate_psi_d(double ha, double hs, double R,
                                             void *opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  Input data{ha, hs, R};
  double sin_psi_d = (ha - hs) / R * (1 - (ha - hs) / 2 / (k(data) * Re + ha)) +
                     R / 2 / (k(data) * Re + ha);
  double psi_d = std::asin(sin_psi_d);
  return psi_d;
}

double EffectiveRadiusModel::calculate_psi_g(double ha, double hs, double R,
                                             void *opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  Input data{ha, hs, R};
  double sin_psi_g = (ha - hs) / R * (1 + (ha - hs) / 2 / (k(data) * Re + ha)) -
                     R / 2 / (k(data) * Re + ha);
  double psi_g = std::asin(sin_psi_g);
  return psi_g;
}

double EffectiveRadiusModel::calculate_phi_e(double psi_d, double psi_g,
                                             void *opaque) {
  double phi_e = psi_d - psi_g;
  return phi_e;
}

RefractionModel::Answer EffectiveRadiusModel::calculate(double ha, double hs,
                                                        double R,
                                                        void *opaque) {
  double psi_d = calculate_psi_d(ha, hs, R);
  double psi_g = calculate_psi_g(ha, hs, R);
  return Answer(
      {.psi_d = psi_d,
       .psi_g = psi_g,
       .d = calculate_d(psi_d, psi_g, reinterpret_cast<void *>(&hs))});
}
