#ifndef FUNCTIONMODEL1D_H
#define FUNCTIONMODEL1D_H
#include <QFile>
#include <vector>
using std::vector;

class FunctionModel1D {
 public:
  virtual double y(double x) = 0;
  struct Point {
    double x;
    double y;
    Point(double x1, double y1) : x{x1}, y{y1} {}
    Point(vector<double> coords) : x{coords[0]}, y{coords[1]} {}
  };
};

#endif  // FUNCTIONMODEL1D_H
