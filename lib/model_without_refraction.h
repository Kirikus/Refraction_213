#ifndef MODEL_WITHOUT_REFRACTION_H
#define MODEL_WITHOUT_REFRACTION_H

#define _USE_MATH_DEFINES
#include <cmath>

// radius of the Earth in meters
const double Re = 6378000;

// Formula for slant range from aircraft to surface target via declination angle and height
// SRle (2.10) from citation
//   R_via_psi_d : lant range from aircraft to surface target, m
//   ha : height of aircraft above sea level, m
//   Re : radius of the Earth, m
//   psi_d : declination angle, radians
double R_via_psi_d(double ha, double psi_d);

// Formula for slant range from aircraft to surface target via sliding angle and height
// SRC: (2.10) from citation
//   R_via_psi_g : lant range from aircraft to surface target, m
//   ha : height of aircraft above sea level, m
//   Re : radius of the Earth, m
//   psi_g : sliding angle, radians
double R_via_psi_g(double ha, double psi_g);

// Formula for length of the arc on the Earth's surface between the nadir direction of the radar and purpose
// SRC: (2.9, 2.11) from citation
//   d : The length of the arc on the Earth's surface between the nadir direction of the radar and purpose, m
//   Re : radius of the Earth, m
//   psi_d : declination angle, radians
//   psi_g : sliding angle, radians
double d(double psi_d, double psi_g);

#endif // MODEL_WITHOUT_REFRACTION_H
