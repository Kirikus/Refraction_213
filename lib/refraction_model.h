#ifndef REFRACTION_MODEL_H
#define REFRACTION_MODEL_H

#define _USE_MATH_DEFINES
#include <cmath>

// radius of the Earth in meters
const double Re = 6378000;

struct RefractionModel {
  // Formula for slant range from aircraft to surface target via declination
  // angle and heights
  virtual double R_via_psi_d(double ha, double hs, double psi_d,
                             void *opaque) = 0;

  // Formula for slant range from aircraft to surface target via sliding angle
  // and height
  virtual double R_via_psi_g(double ha, double hs, double psi_g,
                             void *opaque) = 0;

  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  virtual double d(double psi_d, double psi_g, void *opaque) = 0;

  // Formula for declination angle via slant range, heights of the radar and
  // target
  virtual double psi_d(double ha, double hs, double R, void *opaque) = 0;

  // Formula for sliding angle via slant range, heights of the radar and target
  virtual double psi_g(double ha, double hs, double R, void *opaque) = 0;

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target via heights of the radar and target and slant range
  virtual double phi_e_via_distances(double ha, double hs, double R,
                                     void *opaque) = 0;

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target via sliding and declination angles
  virtual double phi_e_via_angles(double psi_d, double psi_g, void *opaque) = 0;

  // Formula for height of target above sea level via declination angle, height
  // of the radar, slant range
  virtual double hs_via_psi_d(double ha, double psi_d, double R,
                              void *opaque) = 0;
};

#endif  // REFRACTION_MODEL_H
