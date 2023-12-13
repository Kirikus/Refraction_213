#include "angle_calculator.h"

double AngleCalculator::d(double ha, double hs, double psi_g) {
  double N = 1000;
  double dh = (hs - ha) / N;
  double integral = 0;

  for (int i = 0; i < N + 1; ++i) {
    double cos_psi = std::cos(psi_d(ha, ha + dh * i, psi_g));
    if (cos_psi == 1.0) continue;
    integral += cos_psi / std::sqrt(1 - cos_psi * cos_psi) * dh;
  }

  return integral;
}
