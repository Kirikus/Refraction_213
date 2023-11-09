#include "linearmodel.h"

#include <algorithm>
LinearModel::LinearModel() {}

double LinearModel::y(double x) {
  auto start = data.begin();
  auto finish = data.end();
  finish--;
  if (x <= (start->x)) return start->y;
  if (x >= (finish->x)) return finish->y;
  auto second_point = upper_bound(data.begin(), data.end(), x,
                                  [](int x, Point& z) { return x < z.x; });
  auto first_point = second_point;
  first_point--;
  double x1 = (first_point)->x;
  double x2 = (second_point)->x;
  double y1 = (first_point)->y;
  double y2 = (second_point)->y;
  double k = (y2 - y1) / (x2 - x1);
  double b = y1 - k * x1;
  return k * x + b;
}
void LinearModel::fromCSV() {}
