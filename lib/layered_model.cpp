#include "layered_model.h"

double LayeredModel::N(double h) {
  for (int i = 0; i < layeres.size(); ++i)
    if (h <= layeres.at(i)) return atmosheres.at(i)->N(h);
  return atmosheres.back()->N(h);
}
