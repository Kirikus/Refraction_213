#include "average_p_model.h"

double AveragePModel::k(const Input& data) { return 1 / (1 - Re / Ro(data)); }

double AveragePModel::Ro(const Input& data) {
  double Ro_avg = 0;
  const size_t N = 100;
  const double dh = (data.ha - data.hs) / N;
  for (size_t i = 0; i < N; ++i)
    Ro_avg += local_Ro(data, data.hs + dh * i) * dh;
  Ro_avg /= (data.ha - data.hs);
  return Ro_avg;
}

double AveragePModel::local_Ro(const Input& data, double h) {
  ModelWithoutRefraction approximate;
  double psi = approximate.calculate_psi_d(data.ha, data.hs, data.R);
  double delta = std::pow(10, -3);
  return -atmosphere->N(h) /
         (atmosphere->N(h + delta) - atmosphere->N(h - delta)) / std::cos(psi);
}
