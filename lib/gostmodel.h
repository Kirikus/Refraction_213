#ifndef GOSTMODEL_H
#define GOSTMODEL_H
#include <../lib/functionmodel1d.h>

class GOSTModel {
 public:
  GOSTModel(FunctionModel1D* first_model, FunctionModel1D* second_model)
      : p_via_h{first_model}, T_via_h{second_model} {}
  double N(double h);
  double Ro(double);
 private:
  FunctionModel1D* p_via_h;
  FunctionModel1D* T_via_h;


};

#endif  // GOSTMODEL_H
