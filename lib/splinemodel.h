#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H
#include <vector>

#include "functionmodel1d.h"
using std::vector;

class SplineModel : public FunctionModel1D {
 public:
  SplineModel();
  double y(double x) override;
  void fromCSV() override;

 private:
  vector<Point> data;
};
#endif  // SPLINEMODEL_H
