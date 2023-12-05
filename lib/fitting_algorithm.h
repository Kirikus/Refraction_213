#ifndef FITTING_ALGORITHM_H
#define FITTING_ALGORITHM_H

#include <vector>

#include "refraction_aware_model.h"

class FittingAlgorithm : public RefractionAwareModel {
 public:
  virtual Answer calculate(const Input &data, void *opaque) override;
  FittingAlgorithm(std::shared_ptr<AngleCalculator> angle_difference_algorithm,
                   double ha, double hs);

 private:
  std::vector<double> psi_d;
  std::vector<double> psi_g;
  std::vector<double> d;
};
#endif  // FITTING_ALGORITHM_H