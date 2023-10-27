#ifndef MODEL4DIV3_H
#define MODEL4DIV3_H

#include "effective_radius_model.h"

struct Model4div3 : public EffectiveRadiusModel {
  // set k
  virtual double k() override;
};

#endif  // 4DIV3MODEL_H
