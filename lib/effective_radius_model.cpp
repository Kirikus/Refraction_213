#include "effective_radius_model.h"

double EffectiveRadiusModel::calculate_d(double psi_d, double psi_g,
                                         const Input &data) {
  double d = (k(data) * Re + data.hs) * calculate_phi_e(psi_d, psi_g);
  return d;
}

double EffectiveRadiusModel::calculate_psi_d(const Input &data, void *opaque) {
  if (data.R == 0) return 0;  // if target and radar in same dote
  double sin_psi_d =
      (data.ha - data.hs) / data.R *
          (1 - (data.ha - data.hs) / 2 / (k(data) * Re + data.ha)) +
      data.R / 2 / (k(data) * Re + data.ha);
  double psi_d = std::asin(sin_psi_d);
  return psi_d;
}

double EffectiveRadiusModel::calculate_psi_g(const Input &data, void *opaque) {
  if (data.R == 0) return 0;  // if target and radar in same dote
  double sin_psi_g =
      (data.ha - data.hs) / data.R *
          (1 + (data.ha - data.hs) / 2 / (k(data) * Re + data.ha)) -
      data.R / 2 / (k(data) * Re + data.ha);
  double psi_g = std::asin(sin_psi_g);
  return psi_g;
}

double EffectiveRadiusModel::calculate_phi_e(double psi_d, double psi_g,
                                             void *opaque) {
  double phi_e = psi_d - psi_g;
  return phi_e;
}

RefractionModel::Answer EffectiveRadiusModel::calculate(const Input &data,
                                                        void *opaque) {
  double psi_d = calculate_psi_d(data);
  double psi_g = calculate_psi_g(data);
  double hs = data.hs;
  return Answer(
      {.psi_d = psi_d, .psi_g = psi_g, .d = calculate_d(psi_d, psi_g, data)});
}
