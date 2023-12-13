#include "test_linear_model.h"

#include <QApplication>
#include <vector>

#include "../lib/linearmodel.h"
#include "qcustomplot.h"
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(checks_for_values_linear)
std::vector<LinearModel::Point> test_data;

BOOST_AUTO_TEST_CASE(check_dots) {
  test_data.push_back(LinearModel::Point(1, 3));
  test_data.push_back(LinearModel::Point(2, 5));
  test_data.push_back(LinearModel::Point(6, 8));
  test_data.push_back(LinearModel::Point(7, 15));
  LinearModel testModel = LinearModel(test_data);
  for (int i = 0; i < test_data.size(); ++i) {
    BOOST_TEST(testModel.y(test_data[i].x) == test_data[i].y,
               tt::tolerance(1e-6));
  }
}

BOOST_AUTO_TEST_CASE(check_between_dots) {
  test_data.clear();
  test_data.push_back(LinearModel::Point(1, 1));
  test_data.push_back(LinearModel::Point(2, 2));
  LinearModel testModel = LinearModel(test_data);
  BOOST_TEST(testModel.y(1.5) == 1.5, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(graphs_for_linear_interpolation)

void plotting(std::vector<FunctionModel1D::Point>& test_data, int lower_bound,
              int upper_bound) {
  int argc = 1;
  char* argv[] = {"Tests for linear interpolation"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;
  LinearModel spline(test_data);
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  customPlot.graph(0)->setData(x_part, y_part);
  for (int i = lower_bound * 10; i < upper_bound * 10; ++i) {
    x_part.push_back(i / 10.);
    y_part.push_back(spline.y(i / 10.));
  }
  // pass test_data points to graphs:
  customPlot.addGraph();
  customPlot.graph(0)->setData(x_part, y_part);

  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}
std::vector<LinearModel::Point> test_data;

BOOST_AUTO_TEST_CASE(plot_for_linear_interpolation_random) {
  test_data.clear();
  test_data.push_back(LinearModel::Point(3, 5));
  test_data.push_back(LinearModel::Point(5, 6));
  test_data.push_back(LinearModel::Point(6, 3));
  test_data.push_back(LinearModel::Point(7, 8));
  test_data.push_back(LinearModel::Point(9, 15));
  plotting(test_data, 3, 9);
}

BOOST_AUTO_TEST_CASE(plot_for_linear_inerpolation_kx) {
  test_data.clear();
  for (int i = 0; i < 7; ++i) test_data.push_back(LinearModel::Point(i, i));
  plotting(test_data, 1, 6);
}

BOOST_AUTO_TEST_SUITE_END()
