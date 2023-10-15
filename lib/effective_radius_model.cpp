#include "effective_radius_model.h"

double EffectiveRadiusModel::R_via_psi_d(double ha, double hs, double psi_d,
                                         void *opaque) {
  double discriminant =
      std::pow((k * Re + hs), 2) - pow((k * Re + ha) * std::cos(psi_d), 2);
  double R = (k * Re + ha) * std::sin(psi_d) - std::sqrt(discriminant);
  return R;
}

double EffectiveRadiusModel::R_via_psi_g(double ha, double hs, double psi_g,
                                         void *opaque) {
  double discriminant = std::pow((k * Re + hs) * std::sin(psi_g), 2) +
                        2 * (k * Re + hs) * (ha - hs) + std::pow(ha - hs, 2);
  double R = -(k * Re + hs) * std::sin(psi_g) + std::sqrt(discriminant);
  return R;
}

double EffectiveRadiusModel::d(double psi_d, double psi_g, void *opaque) {
  double hs = *(reinterpret_cast<double *>(opaque));
  double d = (k * Re + hs) * phi_e_via_angles(psi_d, psi_g);
  return d;
}

double EffectiveRadiusModel::psi_d(double ha, double hs, double R,
                                   void *opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  double sin_psi_d = (ha - hs) / R * (1 - (ha - hs) / 2 / (k * Re + ha)) +
                     R / 2 / (k * Re + ha);
  double psi_d = std::asin(sin_psi_d);
  return psi_d;
}

double EffectiveRadiusModel::psi_g(double ha, double hs, double R,
                                   void *opaque) {
  if (R == 0) return 0;  // if target and radar in same dote
  double sin_psi_g = (ha - hs) / R * (1 + (ha - hs) / 2 / (k * Re + ha)) -
                     R / 2 / (k * Re + ha);
  double psi_g = std::asin(sin_psi_g);
  return psi_g;
}

double EffectiveRadiusModel::phi_e_via_distances(double ha, double hs, double R,
                                                 void *opaque) {
  double phi_e = psi_d(ha, hs, R) - psi_g(ha, hs, R);
  return phi_e;
}

double EffectiveRadiusModel::phi_e_via_angles(double psi_d, double psi_g,
                                              void *opaque) {
  double phi_e = psi_d - psi_g;
  return phi_e;
}

double EffectiveRadiusModel::hs_via_psi_d(double ha, double psi_d, double R,
                                          void *opaque) {
  double temp = std::pow((k * Re + ha) * std::sin(psi_d) - R, 2) +
                std::pow((k * Re + ha) * std::cos(psi_d), 2);
  double hs = std::sqrt(temp) - k * Re;
  return hs;
}
