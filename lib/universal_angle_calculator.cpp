#include "universal_angle_calculator.h"

#include "refraction_model.h"

double UniversalAngleCalculator::psi_d(double ha, double hs, double psi_g) {
  double cos_psi_d = std::cos(psi_g) * atmosphere->N(hs) / atmosphere->N(ha) *
                     (Re + hs) / (Re + ha);
  return std::acos(cos_psi_d);
}

double UniversalAngleCalculator::psi_g(double ha, double hs, double psi_d) {
  double cos_psi_g = std::cos(psi_d) * atmosphere->N(ha) / atmosphere->N(hs) *
                     (Re + ha) / (Re + hs);
  return std::acos(cos_psi_g);
}
