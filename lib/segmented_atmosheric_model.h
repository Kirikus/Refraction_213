#ifndef SEGMENTED_ATMOSHERIC_MODEL_H
#define SEGMENTED_ATMOSHERIC_MODEL_H

#include "atmospheric_model.h"

struct SegmentedAtmosphericModel : public AtmosphericModel {
  // Formula for refractive index depended on height
  // SRC: (2.27) from citation
  //    N : refractive index, n/u
  //    h : height above sea level, m
  virtual double N(double h) override;

  // Formula for determination height of ground surface above sea level
  // hs : height of ground surface above sea level, m
  void set_hs(double hs);

  // Formula for determination refractive index at the Earth's surface
  // Ns : refractive index at the Earth's surface, n/u
  void set_Ns(double Ns);

 private:
  // height of ground surface above sea level, m
  double hs = 0;
  // refractive index at 1 km above the surface, n/u
  double N1;
  // refractive index at the Earth's surface, n/u
  double Ns = 324.8;
  // exponential decay constant N, n/u
  double H;
  // linear reduction coefficient N per 1 m height, 1/m
  double dN;

  // Formula for linear reduction coefficient N per 1 m height
  // SRC: (2.28) from citation
  void set_dN();

  // Formula for exponential decay constant N
  // SRC: (2.28) from citation
  void set_H();

  // Formula for determination refractive index at 1 km above the surface
  void set_N1();
};

#endif  // SEGMENTED_ATMOSHERIC_MODEL_H
