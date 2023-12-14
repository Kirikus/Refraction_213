#include "iterative_algorithm_for_exponent.h"

IterativeAlgorithmForExponentModel::IterativeAlgorithmForExponentModel(
    std::shared_ptr<AngleCalculatorForExponentModel> angle_difference_algorithm,
    double mu, double eps0, double delta_psi_g)
    : RefractionAwareModel(angle_difference_algorithm),
      mu{mu},
      eps0{eps0},
      delta_psi_g(delta_psi_g) {}

RefractionModel::Answer IterativeAlgorithmForExponentModel::calculate(
    const RefractionModel::Input &data, void *opaque) {
  double psi_g =
      asin((data.ha - data.hs) / data.R *
               (1 + (data.ha - data.hs) / (2 * (1.2 * Re + data.hs))) -
           data.R / (2 * (1.2 * Re + data.hs)));
  double delta_psi_g = 0.1;
  double eps = 1000000;
  while (eps > eps0) {
    double N = 1000;
    double dh = (data.ha - data.hs) / N;
    double R0 = 0;
    double R1 = 0;
    double R2 = 0;
    for (int i = 0; i < N + 1; ++i) {
      double cos_psi_0 = this->angle_difference_algorithm->G(data, data.hs + dh * i) * cos(psi_g);
      R0 += 1 / std::sqrt(1 - cos_psi_0 * cos_psi_0) * dh;
    }
    for (int i = 0; i < N + 1; ++i) {
      double cos_psi_1 =
          this->angle_difference_algorithm->G(data, data.hs + dh * i) * cos(psi_g - delta_psi_g / 2);
      R1 += 1 / std::sqrt(1 - cos_psi_1 * cos_psi_1) * dh;
    }
    for (int i = 0; i < N + 1; ++i) {
      double cos_psi_2 =
          this->angle_difference_algorithm->G(data, data.hs + dh * i) * cos(psi_g + delta_psi_g / 2);
      R2 += 1 / std::sqrt(1 - cos_psi_2 * cos_psi_2) * dh;
    }
    double m = (R2 - R1) / delta_psi_g;
    eps = R0 - data.R;
    psi_g = psi_g - mu * eps / m;
  }
  double psi_d = acos(this->angle_difference_algorithm->G(data, data.ha) * cos(psi_g));
  if (data.ha < data.hs) psi_d = -psi_d;
  double d = angle_difference_algorithm->d(data.ha, data.hs, psi_g);
  return Answer{.psi_d = psi_d, .psi_g = psi_g, .d = d};
}
