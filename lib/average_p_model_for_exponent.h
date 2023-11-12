#ifndef AVERAGE_P_MOSEL_FOR_EXPONENT_H
#define AVERAGE_P_MOSEL_FOR_EXPONENT_H

#include "effective_radius_model.h"
#include "exponent_model.h"

class AveragePModel_forExponent : public EffectiveRadiusModel {
 public:
  // set k : equivalent radius coefficient, n/u
  // SRC: (2.38) from citation
  virtual double k(const Input& data) override;
  AveragePModel_forExponent(const ExponentAtmosphericModel& atmosphere)
      : atmosphere{atmosphere} {}

 private:
  ExponentAtmosphericModel atmosphere;
};

#endif  // AVERAGE_P_MOSEL_FOR_EXPONENT_H
