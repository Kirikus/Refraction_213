#ifndef MODEL4DIV3_H
#define MODEL4DIV3_H

#include "effective_radius_model.h"

struct Model4div3 : public EffectiveRadiusModel {
  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  // SRC: (2.19) from citation
  //    psi_g : sliding angle, radians
  //    psi_d : declination angle, radians
  //    opaque : hs, height of target above sea level, m
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
  // set k
  virtual double k() override;
};

#endif  // 4DIV3MODEL_H
