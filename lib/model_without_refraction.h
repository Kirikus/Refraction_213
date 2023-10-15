#ifndef MODEL_WITHOUT_REFRACTION_H
#define MODEL_WITHOUT_REFRACTION_H

#include "refraction_model.h"

struct ModelWithoutRefraction : public RefractionModel {
  // Formula for slant range from aircraft to surface target via declination
  // angle and heights
  // SRC: (2.10) from citation, image (2.30), inferential
  //   R_via_psi_d : lant range from aircraft to surface target, m
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   psi_d : declination angle, radians
  //   opaque : not used
  virtual double R_via_psi_d(double ha, double hs, double psi_d,
                             void* opaque = nullptr) override;

  // Formula for slant range from aircraft to surface target via sliding angle
  // and height
  // SRC: (2.10) from citation
  //   R_via_psi_g : slant range from aircraft to surface target, m
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   psi_g : sliding angle, radians
  //   opaque : not used
  virtual double R_via_psi_g(double ha, double hs, double psi_g,
                             void* opaque = nullptr) override;

  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  // SRC: (2.9, 2.11) from citation
  //   d : the length of the arc on the Earth's surface between the nadir
  //   direction of the radar and target, m
  //   psi_d : declination angle, radians
  //   psi_g : sliding angle, radians
  //   opaque : not used
  virtual double d(double psi_d, double psi_g, void* opaque = nullptr) override;

  // Formula for declination angle via slant range, heights of the radar and
  // target
  // SRC: image (2.30), inferential
  //   psi_d : declination angle, radians
  //   ha : height of aircraft above sea level, m
  //   hs : height of target above sea level, m
  //   R : slant range from aircraft to surface target, m
  //   opaque : not used
  virtual double psi_d(double ha, double hs, double R,
                       void* opaque = nullptr) override;

  // Formula for sliding angle via slant range, heights of the radar and target
  // SRC: image (2.30), inferential
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
  // SRC: image (2.30), inferential
  //   hs_via_psi_d : height of target above sea level via declination angle,
  //        height of the radar, slant range, m
  //   ha : height of aircraft above sea level, m
  //   psi_d : declination angle, radians R : slant range from aircraft
  //        to surface target, m
  //   R : slant range from aircraft to surface target, m
  //   opaque : not used
  virtual double hs_via_psi_d(double ha, double psi_d, double R,
                              void* opaque = nullptr) override;
};

#endif  // MODEL_WITHOUT_REFRACTION_H
