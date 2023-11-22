#include <QApplication>
#include <vector>

#include "../lib/linearmodel.h"
#include "qcustomplot.h"
#include "test_spline_model.h"
using std::vector;
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(checks_for_values)

vector<LinearModel::Point> test;

BOOST_AUTO_TEST_CASE(check_dots) {
  test.push_back(LinearModel::Point(1, 3));
  test.push_back(LinearModel::Point(2, 5));
  test.push_back(LinearModel::Point(6, 8));
  test.push_back(LinearModel::Point(7, 15));
  LinearModel testModel = LinearModel(test);
  BOOST_TEST(testModel.y(1) == 3, tt::tolerance(1e-6));
  BOOST_TEST(testModel.y(2) == 5, tt::tolerance(1e-6));
  BOOST_TEST(testModel.y(6) == 8, tt::tolerance(1e-6));
  BOOST_TEST(testModel.y(7) == 15, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(check_between_dots) {
  test.clear();
  test.push_back(LinearModel::Point(1, 1));
  test.push_back(LinearModel::Point(2, 2));
  LinearModel testModel = LinearModel(test);
  BOOST_TEST(testModel.y(1.5) == 1.5, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(graphs_for_linear_interpolation)

BOOST_AUTO_TEST_CASE(plot_for_linear_model) {
  int argc = 1;
  char *argv[] = {"Linear interpolation"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;

  vector<LinearModel::Point> data;
  data.push_back(LinearModel::Point(3, 5));
  data.push_back(LinearModel::Point(5, 6));
  data.push_back(LinearModel::Point(6, 3));
  data.push_back(LinearModel::Point(7, 8));
  data.push_back(LinearModel::Point(9, 15));

  LinearModel line(data);

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  for (double i = 3; i < 9; i = i + 0.1) {
    x_part.push_back(i);
    y_part.push_back(line.y(i));
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

BOOST_AUTO_TEST_CASE(plot_for_kx) {
  int argc = 1;
  char *argv[] = {"Linear interpolation for y = kx"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;

  vector<LinearModel::Point> data;
  data.push_back(LinearModel::Point(1, 1));
  data.push_back(LinearModel::Point(2, 2));
  data.push_back(LinearModel::Point(3, 3));
  data.push_back(LinearModel::Point(4, 4));
  data.push_back(LinearModel::Point(5, 5));
  data.push_back(LinearModel::Point(6, 6));

  LinearModel line(data);

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  for (double i = 1; i < 6; i = i + 0.1) {
    x_part.push_back(i);
    y_part.push_back(line.y(i));
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
