#ifndef ITERATIVE_ALGORITHM_H
#define ITERATIVE_ALGORITHM_H

#include "refraction_aware_model.h"

class IterativeAlgorithm : public RefractionAwareModel {
 public:
  virtual Answer calculate(const Input &data, void *opaque = nullptr) override;
  IterativeAlgorithm(
      std::shared_ptr<AngleCalculator> angle_difference_algorithm, double mu,
      double eps0, double delta_psi_g);

 private:
  double delta_psi_g = 0.1;
  double mu = 0.1;
  double eps0 = 0.1;
};
#endif  // ITERATIVE_ALGORITHM_H
