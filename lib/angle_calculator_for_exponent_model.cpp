#include "angle_calculator_for_exponent_model.h"

double AngleCalculatorForExponentModel::psi_d(double ha, double hs,
                                              double psi_g) {
  double Ns = atmosphere.get_Ns();
  double Hb = atmosphere.get_Hb();
  double cos_psi_d = ((Ns) / (Ns * exp(-(ha - hs) / Hb))) *
                     ((Re + hs) / (Re + ha)) * std::cos(psi_g);
  return std::acos(cos_psi_d);
}

double AngleCalculatorForExponentModel::psi_g(double ha, double hs,
                                              double psi_d) {
  double Ns = atmosphere.get_Ns();
  double Hb = atmosphere.get_Hb();
  double cos_psi_g = ((Ns * exp(-(ha - hs) / Hb)) / (Ns)) *
                     ((Re + ha) / (Re + hs)) * std::cos(psi_d);
  return std::acos(cos_psi_g);
}
