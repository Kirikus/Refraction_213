#include "data.h"

#include "mainwindow.h"

#include <cmath>

void addTargetAndStation() {
  int st_coords = user_input_data.getStCoords();
  int trg_coords = user_input_data.getTrgCoords();
  int dist = user_input_data.getDstToTarget();
  user_input_data.plot -> addGraph();
  QVector < double > x_st(1), y_st(1);
  x_st[0] = 100;
  y_st[0] = st_coords;
  user_input_data.plot -> graph(0) -> setData(x_st, y_st);
  QVector < double > x_trg(1), y_trg(1);
  if (dist * dist - (trg_coords - st_coords) * (trg_coords - st_coords) > 0) {
    x_trg[0] = 100 + sqrt(dist * dist - (trg_coords - st_coords) * (trg_coords - st_coords));
    y_trg[0] = trg_coords;
    user_input_data.plot -> graph(0) -> setData(x_st, y_st);
    user_input_data.plot -> graph(0) -> setPen(QColor(255, 50, 70, 255));
    user_input_data.plot -> graph(0) -> setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    user_input_data.plot -> graph(1) -> setData(x_trg, y_trg);
    user_input_data.plot -> graph(1) -> setPen(QColor(0, 255, 70, 255));
    user_input_data.plot -> graph(1) -> setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    user_input_data.plot -> replot();
  }
}
