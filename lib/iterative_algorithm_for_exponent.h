#ifndef ITERATIVEALGORITHMFOREXPONENTMODEL_H
#define ITERATIVEALGORITHMFOREXPONENTMODEL_H

#include "../lib/angle_calculator_for_exponent_model.h"
#include "refraction_aware_model.h"
class IterativeAlgorithmForExponentModel : public RefractionAwareModel {
 public:
  virtual Answer calculate(const Input &data, void *opaque = nullptr) override;
  IterativeAlgorithmForExponentModel(
      std::shared_ptr<AngleCalculatorForExponentModel>
          angle_difference_algorithm,
      double mu, double eps0);

 private:
  double mu = 1;
  double G(const Input &, double);
  double eps0 = 1;
};
#endif  // ITERATIVEALGORITHMFOREXPONENTMODEL_H
