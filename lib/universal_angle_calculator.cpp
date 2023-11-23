#include "universal_angle_calculator.h"

#include "refraction_model.h"

double UniversalAngleCalculator::psi_d(double ha, double hs, double psi_g) {
  double integral = 0;
  double N = 1000;
  double dn = (ha - hs) / N;
  for (int i = 0; i < N; ++i)
    integral += 1 / atmosphere->N(hs + dn * i) *
                (atmosphere->N(hs + dn * (i + 1) - atmosphere->N(hs + dn * i)));
  double cos_psi_d =
      std::cos(psi_g) * exp(-(log((Re + ha) / (Re + hs)) + integral));
  return std::acos(cos_psi_d);
}

double UniversalAngleCalculator::psi_g(double ha, double hs, double psi_d) {
  double integral = 0;
  double N = 1000;
  double dn = (ha - hs) / N;
  for (int i = 0; i < N; ++i)
    integral += 1 / atmosphere->N(hs + dn * i) *
                (atmosphere->N(hs + dn * (i + 1) - atmosphere->N(hs + dn * i)));
  double cos_psi_g =
      std::cos(psi_d) * exp(log((Re + ha) / (Re + hs)) + integral);
  return std::acos(cos_psi_g);
}
