#ifndef EFFECTIVE_RADIUS_MODEL_H
#define EFFECTIVE_RADIUS_MODEL_H

#include "refraction_model.h"

class EffectiveRadiusModel : public RefractionModel {
 public:
  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  // SRC: (2.19) from citation
  //    psi_g : sliding angle, radians
  //    psi_d : declination angle, radians
  //    opaque : Input
  double calculate_d(double psi_d, double psi_g, const Input& data);

  // Formula for declination angle via slant range, heights of the radar and
  // target
  // SRC: (2.17) from citation
  //    psi_d : declination angle, radians
  //    opaque : not used
  double calculate_psi_d(const Input& data, void* opaque = nullptr);

  // Formula for sliding angle via slant range, heights of the radar and target
  // SRC: (2.17) from citation
  //    psi_g : sliding angle, radians
  //    opaque : not used
  double calculate_psi_g(const Input& data, void* opaque = nullptr);

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target
  // SRC: (2.9) from citation
  //    phi_e: angular measure, radians
  //    psi_d : declination angle, radians
  //    psi_g : sliding angle, radians
  double calculate_phi_e(double psi_d, double psi_g, void* opaque = nullptr);

  // Formula for task of the library
  virtual Answer calculate(const Input& data, void* opaque = nullptr) override;

  // equivalent radius coefficient, n/u
  virtual double k(const Input& data) = 0;
};

#endif  // EFFECTIVE_RADIUS_MODEL_H
