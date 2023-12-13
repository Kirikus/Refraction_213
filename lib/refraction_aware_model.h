#ifndef REFRACTIONAWAREMODEL_H
#define REFRACTIONAWAREMODEL_H

#include <memory>

#include "angle_calculator.h"
#include "refraction_model.h"

class RefractionAwareModel : public RefractionModel {
 public:
  RefractionAwareModel(
      std::shared_ptr<AngleCalculator> angle_difference_algorithm)
      : angle_difference_algorithm{angle_difference_algorithm} {}

 protected:
  std::shared_ptr<AngleCalculator> angle_difference_algorithm;
};

#endif  // REFRACTIONAWAREMODEL_H
