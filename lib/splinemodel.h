#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H
#include <vector>

#include "functionmodel1d.h"
using std::vector;

class SplineModel : public FunctionModel1D {
 public:
  SplineModel(vector<Point>);
  SplineModel(QFile&);
  double y(double x) override;

 private:
  struct Data {
    Point first_point;
    Point second_point;
    double a;
    double b;
    double c;
    double d;
    Data(Point p1, Point p2, double a1, double b1, double c1, double d1)
        : first_point{p1}, second_point{p2}, a{a1}, b{b1}, c{c1}, d{d1} {};
  };
  vector<Data> data;
};
#endif  // SPLINEMODEL_H
