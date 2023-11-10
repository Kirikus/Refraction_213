#include <cmath>

#include "data.h"
#include "mainwindow.h"

void addTargetAndStation() {
  double st_height = user_input_data.getStation();
  double trg_height = user_input_data.getTarget();
  double dist = user_input_data.getDistance();
  double recession_koef = 1.1;
  user_input_data.plot->addGraph();
  QVector<double> x_st(1), y_st(1);
  x_st[0] = 100;
  y_st[0] = st_height;
  user_input_data.plot->graph(0)->setData(x_st, y_st);
  QVector<double> x_trg(1), y_trg(1);
  if (!(dist * dist -
                (trg_height - st_height) *
                    (trg_height - st_height) >  // if (input is not correct)
            0 &&
        !std::isnan(trg_height) && !std::isnan(st_height))) {
    return;
  }
  x_trg[0] = 100 + sqrt(dist * dist -
                        (trg_height - st_height) * (trg_height - st_height));
  y_trg[0] = trg_height;
  user_input_data.plot->graph(0)->setData(x_st, y_st);
  user_input_data.plot->graph(0)->setPen(QColor(255, 50, 70, 255));
  user_input_data.plot->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
  user_input_data.plot->graph(1)->setData(x_trg, y_trg);
  user_input_data.plot->graph(1)->setPen(QColor(0, 255, 70, 255));
  user_input_data.plot->graph(1)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
  user_input_data.plot->xAxis->setRange(
      0, std::max((100 + sqrt(dist * dist - (trg_height - st_height) *
                                                (trg_height - st_height))),
                  std::max(y_st[0], y_trg[0])) *
             recession_koef);
  user_input_data.plot->yAxis->setRange(
      0, std::max((100 + sqrt(dist * dist - (trg_height - st_height) *
                                                (trg_height - st_height))),
                  std::max(y_st[0], y_trg[0])) *
             recession_koef);
  user_input_data.plot->replot();
}
