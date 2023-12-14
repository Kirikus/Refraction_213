#ifndef ANGLE_CALCULATOR_FOR_EXPONENT_MODEL_H
#define ANGLE_CALCULATOR_FOR_EXPONENT_MODEL_H

#include "angle_calculator.h"
#include "exponent_model.h"

class AngleCalculatorForExponentModel : public AngleCalculator {
 public:
  // Formula for declination angle
  // SRC: (2.44) from citation
  //    psi_d : declination angle, radians
  //    ha : height of aircraft above sea level, m
  //    hs : height of target above sea level, m
  //    psi_g : sliding angle, radians
  virtual double psi_d(double ha, double hs, double psi_g) override;
  virtual double G(const RefractionModel::Input &data,
                   double h) override;  // TEMPORARY SOLUTION!!
  // Formula for sliding angle
  // SRC: (2.44) from citation
  //    psi_g : sliding angle, radians
  //    ha : height of aircraft above sea level, m
  //    hs : height of target above sea level, m
  //    psi_d : declination angle, radians
  virtual double psi_g(double ha, double hs, double psi_d) override;

  AngleCalculatorForExponentModel(ExponentAtmosphericModel atmosphere)
      : atmosphere{atmosphere} {}

 private:
  ExponentAtmosphericModel atmosphere;
};

#endif  // ANGLE_CALCULATOR_FOR_EXPONENT_MODEL_H
