#ifndef AVERAGE_K_MODEL_H
#define AVERAGE_K_MODEL_H

#include <memory>

#include "atmospheric_model.h"
#include "effective_radius_model.h"
#include "model_without_refraction.h"

class AverageKModel : public EffectiveRadiusModel {
 public:
  // set k : equivalent radius coefficient, n/u
  // opaque : struct Input
  // SRC: (2.38) from citation
  virtual double k(const Input& data) override;

  AverageKModel(std::shared_ptr<AtmosphericModel> atmosphere)
      : atmosphere{atmosphere} {}

 private:
  // SRC: (2.33) from citation
  double Ro(const Input& data, double h);
  // SRC: (2.35) from citation
  double local_k(const Input& data, double h);
  std::shared_ptr<AtmosphericModel> atmosphere = nullptr;
};

#endif  // AVERAGE_K_MODEL_H
