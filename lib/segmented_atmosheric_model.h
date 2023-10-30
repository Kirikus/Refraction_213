#ifndef SEGMENTED_ATMOSHERIC_MODEL_H
#define SEGMENTED_ATMOSHERIC_MODEL_H

#include "atmospheric_model.h"

class SegmentedAtmosphericModel : public AtmosphericModel {
 public:
  // Formula for refractive index depended on height
  // SRC: (2.27) from citation
  //    N : refractive index, n/u
  //    h : height above sea level, m
  virtual double N(double h) override;

  // Set data for atmospheric model
  // hs : height of ground surface above sea level, m
  // Ns : refractive index at the Earth's surface, n/u
  SegmentedAtmosphericModel(double hs = 0, double Ns = 324.8)
      : hs{hs}, Ns{Ns} {}

 private:
  // height of ground surface above sea level, m
  double hs = 0;
  // refractive index at the Earth's surface, n/u
  double Ns = 324.8;

  // Formula for linear reduction coefficient N per 1 m height
  // SRC: (2.28) from citation
  double get_dN();

  // Formula for exponential decay constant N
  // SRC: (2.28) from citation
  double get_H();

  // Formula for determination refractive index at 1 km above the surface
  double get_N1();
};

#endif  // SEGMENTED_ATMOSHERIC_MODEL_H
