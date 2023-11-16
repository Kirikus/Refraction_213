#ifndef MODEL4DIV3_H
#define MODEL4DIV3_H

#include "effective_radius_model.h"

class Model4div3 : public EffectiveRadiusModel {
 public:
  // set k
  // Input data isn't used
  virtual double k(const Input& data) override;
};

#endif  // 4DIV3MODEL_H
