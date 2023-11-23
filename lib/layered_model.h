#ifndef LAYEREDMODEL_H
#define LAYEREDMODEL_H

#include <vector>

#include "atmospheric_model.h"

class LayeredModel : public AtmosphericModel {
 public:
  // atmospheres: pointers to AtmosphericModel
  // layeres: layers' upper limits
  LayeredModel(const std::vector<AtmosphericModel*>& atmosheres,
               const std::vector<double>& layeres)
      : atmosheres{atmosheres}, layeres{layeres} {}
  // Formula for refractive index depended on height
  // SRC: (2.27) from citation
  //    N : refractive index, n/u
  //    h : height above sea level, m
  virtual double N(double h) override;

 private:
  std::vector<AtmosphericModel*> atmosheres;
  std::vector<double> layeres;
};

#endif  // LAYEREDMODEL_H
