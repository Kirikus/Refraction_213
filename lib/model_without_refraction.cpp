#include "model_without_refraction.h"

double ModelWithoutRefraction::R_via_psi_d(double ha, double hs, double psi_d,
                                           void* opaque) {
  double discriminant = pow((Re + ha) * std::sin(psi_d), 2) -
                        2 * Re * (ha - hs) - ha * ha + hs * hs;
  double R = (Re + ha) * std::sin(psi_d) - std::sqrt(discriminant);
  return R;
}

double ModelWithoutRefraction::R_via_psi_g(double ha, double hs, double psi_g,
                                           void* opaque) {
  double discriminant = pow((Re + hs) * std::sin(psi_g), 2) + 2 * Re * ha +
                        ha * ha - 2 * hs * Re - hs * hs;
  double R = -(Re + hs) * std::sin(psi_g) + std::sqrt(discriminant);
  return R;
}

double ModelWithoutRefraction::d(double psi_d, double psi_g, void* opaque) {
  double d = Re * (psi_d - psi_g);
  return d;
}

double ModelWithoutRefraction::psi_d(double ha, double hs, double R,
                                     void* opaque) {
  if (R == 0) return 0;  // if purpose and radar in same dote
  double psi_d =
      std::asin((R * R + ha * ha + 2 * ha * Re - hs * hs - 2 * hs * Re) /
                (2 * R * (Re + ha)));
  return psi_d;
}

double ModelWithoutRefraction::psi_g(double ha, double hs, double R,
                                     void* opaque) {
  if (R == 0) return 0;  // if purpose and radar in same dote
  double psi_g =
      std::asin((R * R - ha * ha - 2 * ha * Re + hs * hs + 2 * hs * Re) /
                (2 * R * (Re + hs)));
  return psi_g;
}

double ModelWithoutRefraction::phi_e(double ha, double hs, double R,
                                     void* opaque) {
  double phi_e = psi_d(ha, hs, R) - psi_g(ha, hs, R);
  return phi_e;
}

double ModelWithoutRefraction::hs_via_psi_d(double ha, double psi_d, double R,
                                            void* opaque) {
  double hs =
      std::sqrt(R * R + pow(ha + Re, 2) - 2 * R * (ha + Re) * std::sin(psi_d)) -
      Re;
  return hs;
}
