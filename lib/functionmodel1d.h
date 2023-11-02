#ifndef FUNCTIONMODEL1D_H
#define FUNCTIONMODEL1D_H
#include <map>
using std::map;

class FunctionModel1D {
 public:
  virtual double y(double x) = 0;
  virtual void fromCSV() = 0;

 protected:
  map<double, double> data;
};

#endif  // FUNCTIONMODEL1D_H
