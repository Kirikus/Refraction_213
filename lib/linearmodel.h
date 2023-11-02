#ifndef LINEARMODEL_H
#define LINEARMODEL_H

#include "functionmodel1d.h"

class LinearModel : public FunctionModel1D {
 public:
  LinearModel();
  double y(double x) override;
  void fromCSV() override;
};

#endif  // LINEARMODEL_H
