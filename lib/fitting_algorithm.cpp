#include "fitting_algorithm.h"

#include "linearmodel.h"
#include "model_without_refraction.h"

RefractionModel::Answer FittingAlgorithm::calculate(
    const RefractionModel::Input &data, void *opaque) {
  ModelWithoutRefraction approximate;
  Answer target_answer = approximate.calculate(data);
  std::vector<FunctionModel1D::Point> point_d;
  std::vector<FunctionModel1D::Point> point_psi_d;
  std::vector<FunctionModel1D::Point> point_psi_g;
  for (int i = 0; i < d.size() && i < psi_d.size() && i < psi_g.size(); ++i) {
    point_d.push_back(FunctionModel1D::Point(d[i], d[i]));
    point_psi_d.push_back(FunctionModel1D::Point(psi_d[i], psi_d[i]));
    point_psi_g.push_back(FunctionModel1D::Point(psi_g[i], psi_g[i]));
  }
  LinearModel interpolate_d(point_d);
  LinearModel interpolate_psi_d(point_psi_d);
  LinearModel interpolate_psi_g(point_psi_g);
  return Answer{.psi_d = interpolate_psi_d.y(target_answer.psi_d),
                .psi_g = interpolate_psi_g.y(target_answer.psi_g),
                .d = interpolate_d.y(target_answer.d)};
}

FittingAlgorithm::FittingAlgorithm(
    std::shared_ptr<AngleCalculator> angle_difference_algorithm, double ha,
    double hs)
    : RefractionAwareModel(angle_difference_algorithm) {
  double N = 1000;
  double d_psi = M_PI / N;
  for (int i = 0; i < N; ++i) {
    psi_g.push_back(i * d_psi);
    psi_d.push_back(angle_difference_algorithm->psi_d(ha, hs, psi_g[i]));
    d.push_back(angle_difference_algorithm->d(ha, hs, psi_g[i]));
  }
}
