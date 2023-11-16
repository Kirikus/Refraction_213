#ifndef REFRACTION_MODEL_H
#define REFRACTION_MODEL_H

#define _USE_MATH_DEFINES
#include <cmath>

// radius of the Earth in meters
const double Re = 6378000;

class RefractionModel {
 public:
  // answer for task
  //    d : the length of the arc on the Earth's surface between the nadir
  //        direction of the radar and target, m
  //    psi_d : declination angle, radians
  //    psi_g : sliding angle, radians
  struct Answer {
    double psi_d;
    double psi_g;
    double d;
  };
  // input data
  // ha : height of aircraft above sea level, m
  // hs : height of target above sea level, m
  // R : slant range from aircraft to surface target, m
  struct Input {
    double ha;
    double hs;
    double R;
  };

  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  virtual double calculate_d(double psi_d, double psi_g, void *opaque) = 0;

  // Formula for declination angle via slant range, heights of the radar and
  // target
  virtual double calculate_psi_d(const Input &data, void *opaque) = 0;

  // Formula for sliding angle via slant range, heights of the radar and target
  virtual double calculate_psi_g(const Input &data, void *opaque) = 0;

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target via sliding and declination angles
  virtual double calculate_phi_e(double psi_d, double psi_g, void *opaque) = 0;

  // Formula for task of the library
  virtual Answer calculate(const Input &data, void *opaque) = 0;
};

#endif  // REFRACTION_MODEL_H
