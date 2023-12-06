#ifndef LINEARMODEL_H
#define LINEARMODEL_H
#include <string>
#include <vector>
using std::string;
#include "functionmodel1d.h"
using std::vector;

class LinearModel : public FunctionModel1D {
 public:
  LinearModel(vector<Point>);
  double y(double x) override;
  LinearModel(string);

 private:
  struct Data {
    double first_x;
    double second_x;
    double k;
    double b;
    Data(double x1, double x2, double k1, double b1)
        : first_x{x1}, second_x{x2}, k{k1}, b{b1} {};
  };
  vector<Data> data;
};

#endif  // LINEARMODEL_H
