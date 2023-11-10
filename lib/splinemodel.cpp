#include "splinemodel.h"

#include <algorithm>

SplineModel::SplineModel() {}

double SplineModel::y(double x) {
  auto start = data.begin();
  auto finish = data.end();
  finish--;
  if (x <= (start->x)) return start->y;
  if (x >= (finish->x)) return finish->y;
  auto second_point = upper_bound(data.begin(), data.end(), x,
                                  [](int x, Point& z) { return x < z.x; });
  auto first_point = second_point;
  first_point--;
  auto third_point = second_point;
  if (second_point == finish) {
    third_point = second_point;
    second_point--;
    first_point--;
  } else {
    third_point = second_point;
    second_point++;
  }
  double x0 = first_point->x;
  double y0 = first_point->y;
  double x1 = second_point->x;
  double y1 = second_point->y;
  double x2 = third_point->x;
  double y2 = third_point->y;
  double a11 = 2 / (x1 - x0);
  double a12 = 1 / (x1 - x0);
  double a21 = 1 / (x1 - x0);
  double a22 = 2 * (1 / (x1 - x0) + 1 / (x2 - x1));
  double a23 = 1 / (x2 - x1);
  double a32 = 1 / (x2 - x1);
  double a33 = 2 / (x2 - x1);
  double b1 = 3 * (y1 - y0) / ((x1 - x0) * (x1 - x0));
  double b2 = 3 * ((y1 - y0) / ((x1 - x0) * (x1 - x0)) +
                   (y2 - y1) / ((x2 - x1) * (x2 - x1)));
  double b3 = 3 * (y2 - y1) / ((x2 - x1) * (x2 - x1));
  double A = a21 * b1 / a11;
  double B = a12 * a21 / a11;
  double C = a22;
  double D = b3 * a23 / a33;
  double E = a23 * a32 / a33;
  double F = b2;
  double k1 = (A + D - F) / (B + E - C);
  double k0 = (b1 - a12 * k1) / a11;
  double k2 = (b3 - a32 * k1) / a33;
  double a1 = k0 * (x1 - x0) - (y1 - y0);
  double c1 = -k1 * (x1 - x0) + (y1 - y0);
  double a2 = k1 * (x2 - x1) - (y2 - y1);
  double c2 = -k2 * (x2 - x1) + (y2 - y1);
  double t = (x - x1) / (x2 - x1);
  if (x > first_point->x && x < second_point->x)
    return (1 - t) * y0 + t * y1 + t * (1 - t) * ((1 - t) * a1 + t * c1);
  else
    return (1 - t) * y1 + t * y2 + t * (1 - t) * ((1 - t) * a2 + t * c2);
}
