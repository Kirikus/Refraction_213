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
  struct IntervalData {
    double first_x;
    double second_x;
    double k;
    double b;
    bool calculated{false};
    IntervalData(double x1, double x2, double k1, double b1)
        : first_x{x1}, second_x{x2}, k{k1}, b{b1}, calculated{true} {};
  };
  vector<IntervalData> interval_data;
};

#endif  // LINEARMODEL_H
