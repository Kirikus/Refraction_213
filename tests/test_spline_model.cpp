#include "test_spline_model.h"

#include <QApplication>

#include "../lib/splinemodel.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

vector<SplineModel::Point> data;

BOOST_AUTO_TEST_SUITE(checks_for_spline_interpolation)

BOOST_AUTO_TEST_CASE(check_dots) {
  data.push_back(SplineModel::Point(-4, -64));
  data.push_back(SplineModel::Point(-3, -27));
  data.push_back(SplineModel::Point(-2, -8));
  data.push_back(SplineModel::Point(-1.5, -3.375));
  data.push_back(SplineModel::Point(-1.4, -2.744));
  data.push_back(SplineModel::Point(-1, -1));

  data.push_back(SplineModel::Point(0, 0));
  data.push_back(SplineModel::Point(0.5, 0.125));
  data.push_back(SplineModel::Point(1, 1));
  data.push_back(SplineModel::Point(1.4, 2.744));
  data.push_back(SplineModel::Point(1.5, 3.375));
  data.push_back(SplineModel::Point(2, 8));

  data.push_back(SplineModel::Point(3, 27));
  data.push_back(SplineModel::Point(4, 64));
  SplineModel spline(data);
  SplineModel testModel = SplineModel(data);
  BOOST_TEST(testModel.y(-4) == -64, tt::tolerance(1e-6));
  BOOST_TEST(testModel.y(-2) == -8, tt::tolerance(1e-6));
  BOOST_TEST(testModel.y(-1) == -1, tt::tolerance(1e-6));
  BOOST_TEST(testModel.y(1.5) == 3.375, tt::tolerance(1e-6));
  BOOST_TEST(testModel.y(2.5) == 15.625, tt::tolerance(0.1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(graphs_for_spline_interpolation)

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_for_x_kub) {
  int argc = 1;
  char *argv[] = {"Spline interpolation for x^3"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;

  vector<SplineModel::Point> data;
  data.push_back(SplineModel::Point(-4, -64));
  data.push_back(SplineModel::Point(-3, -27));
  data.push_back(SplineModel::Point(-2, -8));
  data.push_back(SplineModel::Point(-1.5, -3.375));
  data.push_back(SplineModel::Point(-1.4, -2.744));
  data.push_back(SplineModel::Point(-1, -1));

  data.push_back(SplineModel::Point(0, 0));
  data.push_back(SplineModel::Point(0.5, 0.125));
  data.push_back(SplineModel::Point(1, 1));
  data.push_back(SplineModel::Point(1.4, 2.744));
  data.push_back(SplineModel::Point(1.5, 3.375));
  data.push_back(SplineModel::Point(2, 8));

  data.push_back(SplineModel::Point(3, 27));
  data.push_back(SplineModel::Point(4, 64));
  SplineModel spline(data);

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  for (double i = -4; i < 4; i = i + 0.2) {
    x_part.push_back(i);
    y_part.push_back(spline.y(i));
  }
  // pass data points to graphs:
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x_part, y_part);

  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

#endif

BOOST_AUTO_TEST_CASE(spline_for_random_dots) {
  int argc = 1;
  char *argv[] = {"Spline interpolation for random dots"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;

  vector<SplineModel::Point> data;

  data.push_back(SplineModel::Point(1, 2));
  data.push_back(SplineModel::Point(2, 3));
  data.push_back(SplineModel::Point(4, 1));
  data.push_back(SplineModel::Point(7, 4));
  SplineModel spline(data);

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  for (double i = -4; i < 7; i = i + 0.1) {
    x_part.push_back(i);
    y_part.push_back(spline.y(i));
  }
  // pass data points to graphs:
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x_part, y_part);

  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

BOOST_AUTO_TEST_CASE(plot_for_line) {
  int argc = 1;
  char *argv[] = {"Spline interpolation for line"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;

  vector<SplineModel::Point> data;

  data.push_back(SplineModel::Point(1, 1));
  data.push_back(SplineModel::Point(2, 2));
  data.push_back(SplineModel::Point(3, 3));
  data.push_back(SplineModel::Point(4, 4));
  SplineModel spline(data);

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  for (double i = -1; i < 4; i = i + 0.1) {
    x_part.push_back(i);
    y_part.push_back(spline.y(i));
  }
  // pass data points to graphs:
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x_part, y_part);

  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

BOOST_AUTO_TEST_CASE(plot_for_random_dots_v2) {
  int argc = 1;
  char *argv[] = {"Spline interpolation for random dots"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;

  vector<SplineModel::Point> data;

  data.push_back(SplineModel::Point(1, 2));
  data.push_back(SplineModel::Point(2, 3));
  data.push_back(SplineModel::Point(5, 8));
  data.push_back(SplineModel::Point(6, 12));
  data.push_back(SplineModel::Point(8, 23));
  SplineModel spline(data);

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  for (double i = 1; i < 9; i = i + 0.1) {
    x_part.push_back(i);
    y_part.push_back(spline.y(i));
  }
  // pass data points to graphs:
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x_part, y_part);

  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

BOOST_AUTO_TEST_SUITE_END()
