#ifndef REFRACTIONAWAREMODEL_H
#define REFRACTIONAWAREMODEL_H
#include "angle_calculator.h"

class RefractionAwareModel {
 public:
  virtual double calculate(double, double, double) = 0;
  AngleCalculator* angle_difference_algorithm;
};

#endif  // REFRACTIONAWAREMODEL_H
