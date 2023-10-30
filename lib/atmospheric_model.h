#ifndef ATMOSPHERIC_MODEL_H
#define ATMOSPHERIC_MODEL_H

#include <cmath>

class AtmosphericModel {
 public:
  // Formula for refractive index depended on height
  virtual double N(double h) = 0;
};

#endif  // ATMOSPHERICMODEL_H
