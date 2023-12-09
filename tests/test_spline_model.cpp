#include "test_spline_model.h"

#include <QApplication>

#include "../lib/splinemodel.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(checks_for_spline_interpolation)
std::vector<SplineModel::Point> test_data;
BOOST_AUTO_TEST_CASE(check_dots) {
  test_data.clear();
  for (int i = 0; i < 100; ++i) {
    test_data.push_back(
        SplineModel::Point(double(i) / 10, double(i * i * i) / 1000));
  }
  SplineModel spline(test_data);
  SplineModel testModel = SplineModel(test_data);
  for (int i = 0; i < test_data.size(); ++i)
    BOOST_TEST(testModel.y(test_data[i].x) == test_data[i].y,
               tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(dummy_spline_constructor) {
  std::vector<std::string> test_strings{"1;3", "2;4", "3;5", "6;8"};
  SplineModel simple_spline(test_strings);
  BOOST_TEST(simple_spline.y(1) == 3, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(graphs_for_spline_interpolation)

void plotting(std::vector<FunctionModel1D::Point>& test_data, int lower_bound,
              int upper_bound) {
  int argc = 1;
  char* argv[] = {"Tests for spline interpolation"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));

  QVector<double> x_part, y_part;
  SplineModel spline(test_data);
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

std::vector<SplineModel::Point> test_data;
BOOST_AUTO_TEST_CASE(plot_for_x_kub) {
  for (int i = -80; i < 80; i = i + 10) {
    test_data.push_back(SplineModel::Point(i / 10., i * i * i / 1000.));
  }
  plotting(test_data, -8, 8);
}

BOOST_AUTO_TEST_CASE(spline_for_random_dots) {
  test_data.clear();
  test_data.push_back(SplineModel::Point(1, 2));
  test_data.push_back(SplineModel::Point(2, 3));
  test_data.push_back(SplineModel::Point(4, 1));
  test_data.push_back(SplineModel::Point(7, 4));
  plotting(test_data, -4, 7);
}

BOOST_AUTO_TEST_CASE(plot_for_line) {
  test_data.clear();
  test_data.push_back(SplineModel::Point(1, 1));
  test_data.push_back(SplineModel::Point(2, 2));
  test_data.push_back(SplineModel::Point(3, 3));
  test_data.push_back(SplineModel::Point(4, 4));
  plotting(test_data, -1, 6);
}

BOOST_AUTO_TEST_CASE(spline_for_random_dots_v2) {
  test_data.clear();

  test_data.push_back(SplineModel::Point(1, 2));
  test_data.push_back(SplineModel::Point(2, 3));
  test_data.push_back(SplineModel::Point(5, 8));
  test_data.push_back(SplineModel::Point(6, 12));
  test_data.push_back(SplineModel::Point(8, 23));

  plotting(test_data, 1, 15);
}

BOOST_AUTO_TEST_SUITE_END()
