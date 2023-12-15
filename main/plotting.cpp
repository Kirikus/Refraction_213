#include <cmath>

#include "data.h"
#include "mainwindow.h"

void addTargetAndStation() {
  double st_height = user_input_data.getStation();
  double trg_height = user_input_data.getTarget();
  double dist = user_input_data.getDistance();
  double recession_koef = 1.5;
  QVector<double> x_trg(1), y_trg(1);
  if (!(dist - (trg_height - st_height) >=  // if (input is not correct)
            0 &&
        !std::isnan(trg_height) && !std::isnan(st_height))) {
    return;
  }
  user_input_data.plot->clearGraphs();
  user_input_data.plot->addGraph();
  QVector<double> x_st(1), y_st(1);
  x_st[0] = 0;
  y_st[0] = st_height;
  user_input_data.plot->graph(0)->setData(x_st, y_st);
  x_trg[0] =
      sqrt(dist * dist - (trg_height - st_height) * (trg_height - st_height));
  y_trg[0] = trg_height;
  user_input_data.plot->graph(0)->setName("Станция");
  user_input_data.plot->graph(0)->setData(x_st, y_st);
  user_input_data.plot->graph(0)->setPen(QColor(255, 50, 70, 255));
  user_input_data.plot->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
  user_input_data.plot->addGraph();
  user_input_data.plot->graph(1)->setName("Цель");
  user_input_data.plot->graph(1)->setData(x_trg, y_trg);
  user_input_data.plot->graph(1)->setPen(QColor(0, 255, 70, 255));
  user_input_data.plot->graph(1)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
  double x_dist = x_trg[0] / 2;
  double y_dist = (abs(y_trg[0] - y_st[0])) / 2;
  double x_middle = x_trg[0] / 2;
  double y_middle = (y_trg[0] + y_st[0]) / 2;
  user_input_data.plot->xAxis->setRange(
      std::min(x_middle - x_dist * recession_koef,
               x_middle - y_dist * recession_koef),
      std::max(x_middle + x_dist * recession_koef,
               x_middle + y_dist * recession_koef));
  user_input_data.plot->yAxis->setRange(
      std::min(y_middle - x_dist * recession_koef,
               y_middle - y_dist * recession_koef),
      std::max(y_middle + x_dist * recession_koef,
               y_middle + y_dist * recession_koef));
  user_input_data.plot->legend->setVisible(true);

  // drawing station vector

  QVector<double> station_angle_x(2), station_angle_y(2);
  double vector_length = user_input_data.getDistance() * 0.1;
  station_angle_x[0] = 0;
  station_angle_y[0] = user_input_data.getStation();
  station_angle_x[1] =
      station_angle_x[0] +
      vector_length * std::cos(user_input_data.getDeclinationAngle());
  station_angle_y[1] =
      station_angle_y[0] -
      vector_length * std::sin(user_input_data.getDeclinationAngle());
  user_input_data.plot->addGraph();
  user_input_data.plot->legend
      ->itemWithPlottable(user_input_data.plot->graph(2))
      ->setVisible(false);
  user_input_data.plot->graph(2);
  user_input_data.plot->graph(2)->setData(station_angle_x, station_angle_y);
  user_input_data.plot->graph(2)->setPen(QColor(255, 50, 70, 255));

  // drawing target vector

  QVector<double> target_angle_x(2), target_angle_y(2);
  target_angle_x[0] =
      sqrt(user_input_data.getDistance() * user_input_data.getDistance() -
           (user_input_data.getTarget() - user_input_data.getStation()) *
               (user_input_data.getTarget() - user_input_data.getStation()));
  target_angle_y[0] = user_input_data.getTarget();
  target_angle_x[1] =
      target_angle_x[0] -
      vector_length * std::cos(user_input_data.getSlidingAngle());
  target_angle_y[1] =
      target_angle_y[0] +
      vector_length * std::sin(user_input_data.getSlidingAngle());
  user_input_data.plot->addGraph();
  user_input_data.plot->legend
      ->itemWithPlottable(user_input_data.plot->graph(3))
      ->setVisible(false);
  user_input_data.plot->graph(3);
  user_input_data.plot->graph(3)->setData(target_angle_x, target_angle_y);
  user_input_data.plot->graph(3)->setPen(QColor(0, 255, 70, 255));
  user_input_data.plot->replot();

  // Drawing trajectory

  // QCPCurve *beamTrajectory =
  //   new QCPCurve(user_input_data.plot->xAxis, user_input_data.plot->yAxis);
}
