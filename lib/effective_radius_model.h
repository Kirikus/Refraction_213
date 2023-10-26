#ifndef EFFECTIVE_RADIUS_MODEL_H
#define EFFECTIVE_RADIUS_MODEL_H

#include "refraction_model.h"

struct EffectiveRadiusModel : public RefractionModel {
  virtual double k() = 0;
};

#endif  // EFFECTIVE_RADIUS_MODEL_H
