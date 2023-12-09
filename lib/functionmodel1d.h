#ifndef FUNCTIONMODEL1D_H
#define FUNCTIONMODEL1D_H

class FunctionModel1D {
 public:
  virtual double y(double x) = 0;
  struct Point {
    double x;
    double y;
    Point(double x1, double y1) : x{x1}, y{y1} {}
  };
};

#endif  // FUNCTIONMODEL1D_H
