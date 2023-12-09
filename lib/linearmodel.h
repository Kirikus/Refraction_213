#ifndef LINEARMODEL_H
#define LINEARMODEL_H
#include <string>
#include <vector>

#include "functionmodel1d.h"

class LinearModel : public FunctionModel1D {
 public:
  LinearModel(std::vector<Point>);
  double y(double x) override;
  LinearModel(std::vector<std::string>& file_data);

 private:
  struct Data {
    double first_x;
    double second_x;
    double k;
    double b;
    Data(double x1, double x2, double k1, double b1)
        : first_x{x1}, second_x{x2}, k{k1}, b{b1} {};
  };
  std::vector<Data> data;
};

#endif  // LINEARMODEL_H
