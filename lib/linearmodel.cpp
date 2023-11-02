#include "linearmodel.h"

#include <iostream>
LinearModel::LinearModel() {}

double LinearModel::y(double x) {
  map<double, double>::iterator it_elem = data.find(x);
  if (it_elem != data.end())
    return data[x];
  else {
    map<double, double>::iterator start = data.begin();
    map<double, double>::iterator finish = data.end();
    finish--;
    if (x < (start->first) || x > (finish->first))
      std::runtime_error("Your point is out of bounds!");
    map<double, double>::iterator it_lower = data.lower_bound(x);
    it_lower--;
    map<double, double>::iterator it_higher = data.upper_bound(x);
    double x1 = (it_lower)->first;
    double x2 = (it_higher)->first;
    double y1 = (it_lower)->second;
    double y2 = (it_higher)->second;
    return ((x - x1) * (y2 - y1) / (x2 - x1)) + y1;
  }
}
void LinearModel::fromCSV() {}
