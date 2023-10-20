#ifndef REFRACTION_MODEL_H
#define REFRACTION_MODEL_H

#define _USE_MATH_DEFINES
#include <cmath>

// radius of the Earth in meters
const double Re = 6378000;

struct Answer {
  double psi_d;
  double psi_g;
  double d;
  Answer(double psi_d, double psi_g, double d)
      : psi_d{psi_d}, psi_g{psi_g}, d{d} {}
};

struct RefractionModel {
  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  virtual double calculate_d(double psi_d, double psi_g, void *opaque) = 0;

  // Formula for declination angle via slant range, heights of the radar and
  // target
  virtual double calculate_psi_d(double ha, double hs, double R,
                                 void *opaque) = 0;

  // Formula for sliding angle via slant range, heights of the radar and target
  virtual double calculate_psi_g(double ha, double hs, double R,
                                 void *opaque) = 0;

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target via sliding and declination angles
  virtual double calculate_phi_e(double psi_d, double psi_g, void *opaque) = 0;

  // Formula for task of the library
  virtual Answer calculate(double ha, double hs, double R, void *opaque) = 0;

 protected:
  // height of target above sea level, m
  double hs;

  // height of aircraft above sea level, m
  double ha;

  // slant range from aircraft to surface target, m
  double R;

  // declination angle, radians
  double psi_d;

  // sliding angle, radians
  double psi_g;

  // length of the arc on the Earth's surface between the nadir direction of the
  // radar and target
  double d;

  // angular measure of the arc of the Earth's surface from the radar to the
  // target
  double phi_e;
};

#endif  // REFRACTION_MODEL_H
