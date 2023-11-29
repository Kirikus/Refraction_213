#include "universal_angle_calculator.h"

#include "refraction_model.h"

double UniversalAngleCalculator::psi_d(double ha, double hs, double psi_g) {
  double integral = 0;
  double N = 1000;
  double dh = (ha - hs) / 1000;
  for (int i = 1; i < N; ++i)
    integral += 1 / atmosphere->N(hs + dh * i) *
                (atmosphere->N(hs + dh * i) - atmosphere->N(hs + dh * (i - 1)));
  double cos_psi_d = std::cos(psi_g) * exp(-integral) * (Re + hs) / (Re + ha);
  return std::acos(cos_psi_d);
}

double UniversalAngleCalculator::psi_g(double ha, double hs, double psi_d) {
  double integral = 0;
  double N = 1000;
  double dh = (ha - hs) / 1000;
  for (int i = 1; i < N; ++i)
    integral += 1 / atmosphere->N(hs + dh * i) *
                (atmosphere->N(hs + dh * i) - atmosphere->N(hs + dh * (i - 1)));
  double cos_psi_g = std::cos(psi_d) * exp(integral) * (Re + ha) / (Re + hs);
  return std::acos(cos_psi_g);
}
