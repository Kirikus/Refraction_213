#include "fitting_algorithm.h"

#include "model_without_refraction.h"

int binary_search(double target_d, std::vector<double> d) {
  for (int i = d.size() / 2, start = 0, finish = d.size();;) {
    if (finish - start == 1) return start;
    if (d.at(i) < target_d) {
      start = i;
      i = (finish - start) / 2;
    }
    if (d.at(i) > target_d) {
      finish = i;
      i = (finish - start) / 2;
    }
    if (d.at(i) == target_d) return i;
  }
}

RefractionModel::Answer FittingAlgorithm::calculate(
    const RefractionModel::Input &data, void *opaque) {
  ModelWithoutRefraction approximate;
  double target_d = approximate.calculate(data).d;
  int i = binary_search(target_d, d);
  return Answer{.psi_d = psi_d[i], .psi_g = psi_g[i], .d = d[i]};
}

FittingAlgorithm::FittingAlgorithm(
    std::shared_ptr<AngleCalculator> angle_difference_algorithm, double ha,
    double hs)
    : RefractionAwareModel(angle_difference_algorithm) {
  double N = 1000;
  double d_psi = M_PI / 1000;
  for (int i = 0; i < N; ++i) {
    psi_g[i] = i * d_psi;
    psi_d[i] = angle_difference_algorithm->psi_d(ha, hs, psi_g[i]);
    d[i] = angle_difference_algorithm->d(ha, hs, psi_g[i]);
  }
}
