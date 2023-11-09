#ifndef LINEARMODEL_H
#define LINEARMODEL_H
#include <vector>

#include "functionmodel1d.h"
using std::vector;

class LinearModel : public FunctionModel1D {
 public:
  LinearModel();
  double y(double x) override;
  void fromCSV() override;

 private:
  vector<Point> data;
};

#endif  // LINEARMODEL_H
