#ifndef ANGLE_CALCULATOR_H
#define ANGLE_CALCULATOR_H

#include <memory>

#include "atmospheric_model.h"

class AngleCalculator {
  // Formula for declination angle
  // psi_d : declination angle, radians
  // ha : height of aircraft above sea level, m
  // hs : height of target above sea level, m
  // psi_g : sliding angle, radians
  virtual double psi_d(double ha, double hs, double psi_g) = 0;

  // Formula for sliding angle
  // psi_g : sliding angle, radians
  // ha : height of aircraft above sea level, m
  // hs : height of target above sea level, m
  // psi_d : declination angle, radians
  virtual double psi_g(double ha, double hs, double psi_d) = 0;
};

#endif  // ANGLE_CALCULATOR_H
