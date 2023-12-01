#include "angle_calculator_for_exponent_model.h"

double AngleCalculatorForExponentModel::psi_d(double ha, double hs,
                                              double psi_g) {
  double Ns = atmosphere.get_Ns();
  double Hb = atmosphere.get_Hb();
  double cos_psi_d =
      ((1 + pow(10, -6) * Ns) / (1 + pow(10, -6) * Ns * exp(-(ha - hs) / Hb))) *
      ((Re + hs) / (Re + ha)) * std::cos(psi_g);
  return std::acos(cos_psi_d);
}

double AngleCalculatorForExponentModel::psi_g(double ha, double hs,
                                              double psi_d) {
  double Ns = atmosphere.get_Ns();
  double Hb = atmosphere.get_Hb();
  double cos_psi_g =
      ((1 + pow(10, -6) * Ns * exp(-(ha - hs) / Hb)) / (1 + pow(10, -6) * Ns)) *
      ((Re + ha) / (Re + hs)) * std::cos(psi_d);
  return std::acos(cos_psi_g);
}
