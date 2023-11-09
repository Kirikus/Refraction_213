#ifndef FUNCTIONMODEL1D_H
#define FUNCTIONMODEL1D_H

class FunctionModel1D {
 public:
  virtual double y(double x) = 0;
  virtual void fromCSV() = 0;
  struct Point {
    double x;
    double y;
  };
};

#endif  // FUNCTIONMODEL1D_H
