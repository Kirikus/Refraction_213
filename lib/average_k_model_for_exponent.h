#ifndef AVERAGE_K_MODEL_FOREXPONENT_H
#define AVERAGE_K_MODEL_FOREXPONENT_H

#include "effective_radius_model.h"
#include "exponent_model.h"

class AverageKModel_forExponent : public EffectiveRadiusModel {
 public:
  // set k : equivalent radius coefficient, n/u
  // SRC: (2.38) from citation
  virtual double k(const Input& data) override;
  AverageKModel_forExponent(const ExponentAtmosphericModel& atmosphere)
      : atmosphere{atmosphere} {}

 private:
  ExponentAtmosphericModel atmosphere;
};

#endif  // AVERAGE_K_MODEL_FOREXPONENT_H
