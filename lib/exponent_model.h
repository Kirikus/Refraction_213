#ifndef EXPONENTMODEL_H
#define EXPONENTMODEL_H

#include "atmospheric_model.h"
#include "model_without_refraction.h"

class ExponentAtmosphericModel : public AtmosphericModel {
 public:
  // Formula for refractive index depended on height
  // SRC: (2.29-2.32) from citation
  //    N : refractive index, n/u
  //    h : height above sea level, m
  virtual double N(double h) override;

  // Set data for atmospheric model
  // hs : height of ground surface above sea level, m
  // Ns : refractive index at the Earth's surface, n/u
  ExponentAtmosphericModel(double hs = 0, double Ns = 324.8) : hs{hs}, Ns{Ns} {}

  double get_Hb();
  double get_Ns();

 private:
  // height of ground surface above sea level, m
  double hs = 0;
  // refractive index at the Earth's surface, n/u
  double Ns = 324.8;

  double hb = 12192;
  double Nb = 66.65;
};

#endif  // EXPONENTMODEL_H
