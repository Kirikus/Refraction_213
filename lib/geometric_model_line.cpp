#include "geometric_model_line.h"

RefractionModel::Answer GeometricModelLine::calculate(
    const RefractionModel::Input &data, void *opaque) {
  if (data.R == 0) return Answer{.psi_d = 0, .psi_g = 0, .d = 0};
  double psi = std::asin(abs(data.ha - data.hs) / data.R);
  double d = data.R * std::cos(psi);
  return Answer{.psi_d = psi, .psi_g = psi, .d = d};
}
