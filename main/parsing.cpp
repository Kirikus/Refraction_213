#include "parsing.h"

double parse_double(std::string to_parse) {
  int cnt = 0;
  double res = 0;
  for (int i = 0; i < to_parse.size(); ++i) {
    if (to_parse[i] == ',') {
      break;
    } else {
      res = res * 10 + to_parse[cnt++] - '0';
    }
  }
  if (cnt == to_parse.size())
    return res;
  double fraction = 0;
  double frac_order = 1;
  for (int i = cnt + 1; i < to_parse.size(); ++i) {
    fraction = fraction * 10 + (to_parse[i] - '0');
    frac_order *= 10;
  }
  return res + fraction / frac_order;
}
