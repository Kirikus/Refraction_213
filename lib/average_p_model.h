#ifndef AVERAGE_P_MODEL_H
#define AVERAGE_P_MODEL_H

#include <memory>

#include "effective_radius_model.h"
#include "model_without_refraction.h"

class AveragePModel : public EffectiveRadiusModel {
 public:
  // set k : equivalent radius coefficient, n/u
  // opaque : struct Input
  // SRC: (2.40) from citation
  virtual double k(const Input& data) override;
  AveragePModel(std::shared_ptr<AtmosphericModel> atmosphere);

 private:
  // SRC: (2.39) from citation
  double Ro(const Input& data);
  // SRC: (2.33) from citation
  double local_Ro(const Input& data, double h);
  std::shared_ptr<AtmosphericModel> atmosphere = nullptr;
};

#endif  // AVERAGE_P_MODEL_H
