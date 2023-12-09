#include "iterative_algorithm_for_exponent.h"

IterativeAlgorithmForExponentModel::IterativeAlgorithmForExponentModel(
    std::shared_ptr<AngleCalculatorForExponentModel> angle_difference_algorithm,
    double mu, double eps0)
    : RefractionAwareModel(angle_difference_algorithm), mu{mu}, eps0{eps0} {}

double IterativeAlgorithmForExponentModel::G(const RefractionModel::Input &data,
                                             double h) {
  return cos(angle_difference_algorithm->psi_d(
      h, data.hs, 0));  // I am not quite sure if I can do it another way
}

RefractionModel::Answer IterativeAlgorithmForExponentModel::calculate(
    const RefractionModel::Input &data, void *opaque) {
  double psi_g =
      asin((data.ha - data.hs) / data.R *
               (1 + (data.ha - data.hs) / (2 * (1.2 * Re + data.hs))) -
           data.R / (2 * (1.2 * Re + data.hs)));
  double delta_psi_g = 0.1;
  double eps = 10000000000;
  while (eps > eps0) {
    double N = 1000;
    double dh = (data.hs - data.ha) / N;
    double R0 = 0;
    double R1 = 0;
    double R2 = 0;
    for (int i = 0; i < N + 1; ++i) {
      double cos_psi = G(data, data.ha + dh * i) * cos(psi_g);
      R0 += 1 / std::sqrt(1 - cos_psi * cos_psi) * dh;
    }
    for (int i = 0; i < N + 1; ++i) {
      double cos_psi = G(data, data.ha + dh * i) * cos(psi_g - delta_psi_g / 2);
      R1 += 1 / std::sqrt(1 - cos_psi * cos_psi) * dh;
    }
    for (int i = 0; i < N + 1; ++i) {
      double cos_psi = G(data, data.ha + dh * i) * cos(psi_g + delta_psi_g / 2);
      R2 += 1 / std::sqrt(1 - cos_psi * cos_psi) * dh;
    }
    double m = (R2 - R1) / delta_psi_g;
    eps = R0 - data.R;
    psi_g = psi_g - mu * eps / m;
  }
  double psi_d = acos(G(data, data.ha) * cos(psi_g));
  double d = angle_difference_algorithm->d(data.ha, data.hs, psi_g);
  return Answer{.psi_d = psi_d, .psi_g = psi_g, .d = d};
}
