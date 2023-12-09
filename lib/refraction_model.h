#ifndef REFRACTION_MODEL_H
#define REFRACTION_MODEL_H

#define _USE_MATH_DEFINES
#include <cmath>

// radius of the Earth in meters
const double Re = 6378000;

class RefractionModel {
 public:
  // answer for task
  //    d : the length of the arc on the Earth's surface between the nadir
  //        direction of the radar and target, m
  //    psi_d : declination angle, radians
  //    psi_g : sliding angle, radians
  struct Answer {
    double psi_d;
    double psi_g;
    double d;
  };
  // input data
  // ha : height of aircraft above sea level, m
  // hs : height of target above sea level, m
  // R : slant range from aircraft to surface target, m
  struct Input {
    double ha;
    double hs;
    double R;
  };

  // Formula for task of the library
  virtual Answer calculate(const Input &data, void *opaque = nullptr) = 0;

  // answer for reverse task
  // hs : height of target above sea level, m
  // d : the length of the arc on the Earth's surface between the nadir
  //        direction of the radar and target, m
  struct AnswerReverseTask {
    double hs;
    double d;
  };

  AnswerReverseTask calculate_reverse_task(double ha, double psi_d, double R,
                                           double hs /*initial hs*/);
};

#endif  // REFRACTION_MODEL_H
