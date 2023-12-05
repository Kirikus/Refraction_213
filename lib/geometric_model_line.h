#ifndef GEOMETRIC_MODEL_LINE_H
#define GEOMETRIC_MODEL_LINE_H

#include "refraction_model.h"

class GeometricModelLine : public RefractionModel {
 public:
  virtual Answer calculate(const Input &data, void *opaque = nullptr) override;
};

#endif  // GEOMETRIC_MODEL_LINE_H
