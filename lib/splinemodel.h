#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H
#include <string>
#include <vector>
using std::string;

#include "functionmodel1d.h"
using std::vector;

class SplineModel : public FunctionModel1D {
 public:
  SplineModel(std::vector<Point>);
  SplineModel(string);
  double y(double x) override;

 private:
  struct Data {
    double first_x;
    double second_x;
    double a;
    double b;
    double c;
    double d;
    Data(double x0, double x1, double a1, double b1, double c1, double d1)
        : first_x{x0}, second_x{x1}, a{a1}, b{b1}, c{c1}, d{d1} {};
  };
  vector<Data> data;
};
#endif  // SPLINEMODEL_H
