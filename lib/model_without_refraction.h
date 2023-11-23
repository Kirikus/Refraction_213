#ifndef MODEL_WITHOUT_REFRACTION_H
#define MODEL_WITHOUT_REFRACTION_H

#include "refraction_model.h"

class ModelWithoutRefraction : public RefractionModel {
 public:
  // Formula for length of the arc on the Earth's surface between the nadir
  // direction of the radar and target
  // SRC: (2.9, 2.11) from citation
  //    d : the length of the arc on the Earth's surface between the nadir
  //    direction of the radar and target, m
  //    psi_d : declination angle, radians
  //    psi_g : sliding angle, radians
  //    opaque : not used
  double calculate_d(double psi_d, double psi_g, void* opaque = nullptr);

  // Formula for declination angle via slant range, heights of the radar and
  // target
  // SRC: image (2.30), inferential
  //    psi_d : declination angle, radians
  //    opaque : not used
  double calculate_psi_d(const Input& data, void* opaque = nullptr);

  // Formula for sliding angle via slant range, heights of the radar and target
  // SRC: image (2.30), inferential
  //    psi_g : sliding angle, radians
  //    opaque : not used
  double calculate_psi_g(const Input& data, void* opaque = nullptr);

  // Formula for angular measure of the arc of the Earth's surface from the
  // radar to the target
  // SRC: (2.9) from citation
  //    phi_e : angular measure, radians
  //    psi_d : declination angle, radians
  //    psi_g : sliding angle, radians
  double calculate_phi_e(double psi_d, double psi_g, void* opaque = nullptr);

  // Formula for task of the library
  virtual Answer calculate(const Input& data, void* opaque = nullptr) override;
};

#endif  // MODEL_WITHOUT_REFRACTION_H
