#ifndef EFFECTIVE_RADIUS_MODEL_H
#define EFFECTIVE_RADIUS_MODEL_H

#include "refraction_model.h"

struct EffectiveRadiusModel : public RefractionModel {
  const double k = 4 / 3;

  // Formula for slant range from aircraft to surface target via declination
  // angle and heights
  // SRC: (2.18) from citation
  //   R : slant range from aircraft to surface target, m
  //   psi_d : declination angle, radians
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   opaque : not used
  virtual double R_via_psi_d(double ha, double hs, double psi_d,
                             void* opaque = nullptr) override;

  // Formula for slant range from aircraft to surface target via sliding angle
  // and height
  // SRC: (2.18) from citation
  //   R : slant range from aircraft to surface target, m
  //   psi_g : sliding angle, radians
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   opaque : not used
  virtual double R_via_psi_g(double ha, double hs, double psi_g,
                             void* opaque = nullptr) override;

  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  // SRC: (2.19) from citation
  //   psi_g : sliding angle, radians
  //   psi_d : declination angle, radians
  //   opaque : hs, height of target above sea level, m
  virtual double d(double psi_d, double psi_g, void* opaque) override;

  // Formula for declination angle via slant range, heights of the radar and
  // target
  // SRC: (2.17) from citation
  //   psi_d : declination angle, radians
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   R : slant range from aircraft to surface target, m
  //   opaque : not used
  virtual double psi_d(double ha, double hs, double R,
                       void* opaque = nullptr) override;

  // Formula for sliding angle via slant range, heights of the radar and target
  // SRC: (2.17) from citation
  //   psi_g : sliding angle, radians
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   R : slant range from aircraft to surface target, m
  //   opaque : not used
  virtual double psi_g(double ha, double hs, double R,
                       void* opaque = nullptr) override;

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target
  // SRC: (2.9) from citation
  //   phi_e_via_distances : angular measure, radians
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   R : slant range from aircraft to surface target, m
  //   opaque : not used
  virtual double phi_e_via_distances(double ha, double hs, double R,
                                     void* opaque = nullptr) override;

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target
  // SRC: (2.9) from citation
  //   phi_e_via_distances : angular measure, radians
  //   psi_d : declination angle, radians
  //   psi_g : sliding angle, radians
  virtual double phi_e_via_angles(double psi_d, double psi_g,
                                  void* opaque = nullptr) override;

  // Formula for height of target above sea level via declination angle, height
  // of the radar, slant range
  // SRC: (2.18) from citation
  //   hs : height of target above sea level, m
  //   R : slant range from aircraft to surface target, m
  //   psi_g : sliding angle, radians
  //   ha : height of aircraft above sea level, m
  //   opaque : not used
  virtual double hs_via_psi_d(double ha, double psi_d, double R,
                              void* opaque = nullptr) override;
};

#endif  // EFFECTIVE_RADIUS_MODEL_H
