#ifndef ITERATIVE_ALGORITHM_FOR_EXPONENT_H
#define ITERATIVE_ALGORITHM_FOR_EXPONENT_H

#include "../lib/angle_calculator_for_exponent_model.h"
#include "refraction_aware_model.h"
class IterativeAlgorithmForExponentModel : public RefractionAwareModel {
 public:
  virtual Answer calculate(const Input &data, void *opaque = nullptr) override;
  IterativeAlgorithmForExponentModel(
      std::shared_ptr<AngleCalculatorForExponentModel>
          angle_difference_algorithm,
      double mu, double eps0, double delta_psi_g);

 private:
  double mu = 0.1;
  double eps0 = 0.1;
  double delta_psi_g = 0.1;
};
#endif  // ITERATIVE_ALGORITHM_FOR_EXPONENT_H
