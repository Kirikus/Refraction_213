#include "fitting_algorithm.h"

#include "linearmodel.h"
#include "model_without_refraction.h"

RefractionModel::Answer FittingAlgorithm::calculate(
    const RefractionModel::Input &data, void *opaque) {
  ModelWithoutRefraction approximate;
  Answer target_answer = approximate.calculate(data);

  std::vector<FunctionModel1D::Point> point_psi_g;
  for (int i = 0; i < psi_g.size(); ++i) {
    point_psi_g.push_back(FunctionModel1D::Point(psi_g[i], psi_g[i]));
  }

  LinearModel interpolate_psi_g(point_psi_g);
  double psi_g_res = interpolate_psi_g.y(target_answer.psi_g);
  return Answer{
      .psi_d = angle_difference_algorithm->psi_d(data.ha, data.hs, psi_g_res),
      .psi_g = psi_g_res,
      .d = angle_difference_algorithm->d(data.ha, data.hs, psi_g_res)};
}

FittingAlgorithm::FittingAlgorithm(
    std::shared_ptr<AngleCalculator> angle_difference_algorithm, double ha,
    double hs)
    : RefractionAwareModel(angle_difference_algorithm) {
  double N = 1000;
  double d_psi = 2 * M_PI / N;
  for (int i = 0; i < N; ++i) {
    psi_g.push_back(-M_PI + i * d_psi);
  }
}
