#ifndef EFFECTIVE_RADIUS_MODEL_H
#define EFFECTIVE_RADIUS_MODEL_H

#include "atmospheric_model.h"
#include "refraction_model.h"

class EffectiveRadiusModel : public RefractionModel {
 public:
  // input data for k
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
  // SRC: (2.19) from citation
  //    psi_g : sliding angle, radians
  //    psi_d : declination angle, radians
  //    opaque : Input
  virtual double calculate_d(double psi_d, double psi_g, void* opaque) override;

  // Formula for declination angle via slant range, heights of the radar and
  // target
  // SRC: (2.17) from citation
  //    psi_d : declination angle, radians
  //    ha : height of aircraft above sea level, m
  //    hs : height of target above sea level, m
  //    R : slant range from aircraft to surface target, m
  //    opaque : not used
  virtual double calculate_psi_d(double ha, double hs, double R,
                                 void* opaque = nullptr) override;

  // Formula for sliding angle via slant range, heights of the radar and target
  // SRC: (2.17) from citation
  //    psi_g : sliding angle, radians
  //    ha : height of aircraft above sea level, m
  //    hs : height of target above sea level, m
  //    R : slant range from aircraft to surface target, m
  //    opaque : not used
  virtual double calculate_psi_g(double ha, double hs, double R,
                                 void* opaque = nullptr) override;

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target
  // SRC: (2.9) from citation
  //    phi_e: angular measure, radians
  //    psi_d : declination angle, radians
  //    psi_g : sliding angle, radians
  virtual double calculate_phi_e(double psi_d, double psi_g,
                                 void* opaque = nullptr) override;

  // Formula for task of the library
  virtual Answer calculate(double ha, double hs, double R,
                           void* opaque = nullptr) override;

  // equivalent radius coefficient, n/u
  virtual double k(const Input& data) = 0;
};

#endif  // EFFECTIVE_RADIUS_MODEL_H
