#ifndef UNIVERSAL_ANGLE_CALCULATOR_H
#define UNIVERSAL_ANGLE_CALCULATOR_H

#include "angle_calculator.h"

class UniversalAngleCalculator : public AngleCalculator {
 public:
  // Formula for declination angle
  // SRC: (2.42) from citation
  //    psi_d : declination angle, radians
  //    ha : height of aircraft above sea level, m
  //    hs : height of target above sea level, m
  //    psi_g : sliding angle, radians
  virtual double psi_d(double ha, double hs, double psi_g) override;

  // Formula for sliding angle
  // SRC: (2.42) from citation
  //    psi_g : sliding angle, radians
  //    ha : height of aircraft above sea level, m
  //    hs : height of target above sea level, m
  //    psi_d : declination angle, radians
  virtual double psi_g(double ha, double hs, double psi_d) override;
  virtual double G(const RefractionModel::Input &data,
                   double h) override;  // TEMPORARY SOLUTION!!!
  UniversalAngleCalculator(std::shared_ptr<AtmosphericModel> atmosphere)
      : atmosphere{atmosphere} {}

 private:
  std::shared_ptr<AtmosphericModel> atmosphere;
};

#endif  // UNIVERSAL_ANGLE_CALCULATOR_H
