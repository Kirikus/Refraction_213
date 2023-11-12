#include "average_k_model.h"

double AverageKModel::k(const Input& data) {
  double k_avg = 0;
  const size_t N = 100;
  const double dh = (data.ha - data.hs) / N;
  for (size_t i = 0; i < N; ++i) k_avg += local_k(data, data.hs + dh * i) * dh;
  k_avg /= (data.ha - data.hs);
  return k_avg;
}

double AverageKModel::Ro(const Input& data, double h) {
  ModelWithoutRefraction approximate;
  double psi = approximate.calculate_psi_d(data.ha, data.hs, data.R);
  double delta = std::pow(10, -3);
  return -atmosphere->N(h) /
         (atmosphere->N(h + delta) - atmosphere->N(h - delta)) / std::cos(psi);
}

double AverageKModel::local_k(const Input& data, double h) {
  return 1 / (1 - Re / Ro(data, h));
}
