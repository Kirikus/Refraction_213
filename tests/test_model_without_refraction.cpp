#include "test_model_without_refraction.h"

#include <QApplication>

#include "../lib/model_without_refraction.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(d_without_refraction)

ModelWithoutRefraction testModel;

BOOST_AUTO_TEST_CASE(d_simple) {
  BOOST_TEST(testModel.calculate_d(M_PI / 3, M_PI / 6) == Re * M_PI / 6,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(psi_d_without_refraction)

ModelWithoutRefraction testModel;

BOOST_AUTO_TEST_CASE(simple) {
  RefractionModel::Input data{.ha = 0, .hs = 0, .R = 0};
  BOOST_TEST(testModel.calculate_psi_d(data) == 0);
}

BOOST_AUTO_TEST_CASE(equilateral_triangle) {
  RefractionModel::Input data{.ha = 2000, .hs = 2000, .R = Re + 2000};
  BOOST_TEST(testModel.calculate_psi_d(data) == M_PI / 6, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(psi_d_pi_2) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1000};
  BOOST_TEST(testModel.calculate_psi_d(data) == M_PI / 2, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(same_dote) {
  RefractionModel::Input data{.ha = 2000, .hs = 2000, .R = 0};
  BOOST_TEST(testModel.calculate_psi_d(data) == 0, tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_for_psi_d) {
  int argc = 1;
  char *argv[] = {"psi_d"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  // bins for hs
  const int N = 100;
  const double h_min = 1000, h_max = 3 * 1000;
  QVector<double> x(N), y(N);
  const double R = 1000;   // distance between target and radar
  const double ha = 2000;  // high of radar

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.xAxis->setLabel("hs, km");
  customPlot.yAxis->setLabel("psi_d, radians");

  for (int j = 0; j < N; ++j) {
    x[j] = (h_min + j * (h_max - h_min) / (N - 1)) / 1000;
    RefractionModel::Input data{.ha = ha, .hs = x[j] * 1000, .R = R};
    y[j] = testModel.calculate_psi_d(data);
  }

  // pass data points to graphs:
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x, y);

  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(psi_g_without_refraction)

ModelWithoutRefraction testModel;

BOOST_AUTO_TEST_CASE(simple) {
  RefractionModel::Input data{.ha = 0, .hs = 0, .R = 0};
  BOOST_TEST(testModel.calculate_psi_g(data) == 0);
}

BOOST_AUTO_TEST_CASE(equilateral_triangle) {
  RefractionModel::Input data{.ha = 2000, .hs = 2000, .R = Re + 2000};
  BOOST_TEST(testModel.calculate_psi_g(data) == -M_PI / 6, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(psi_g_pi_2) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1000};
  BOOST_TEST(testModel.calculate_psi_g(data) == M_PI / 2, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(same_dote) {
  RefractionModel::Input data{.ha = 2000, .hs = 2000, .R = 0};
  BOOST_TEST(testModel.calculate_psi_g(data) == 0, tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_for_psi_g) {
  int argc = 1;
  char *argv[] = {"psi_g"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  // bins for hs
  const int N = 100;
  const double h_min = 1000, h_max = 3 * 1000;
  QVector<double> x(N), y(N);
  const double R = 1000;   // distance between target and radar
  const double ha = 2000;  // high of radar

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.xAxis->setLabel("hs, km");
  customPlot.yAxis->setLabel("psi_g, radians");

  for (int j = 0; j < N; ++j) {
    x[j] = (h_min + j * (h_max - h_min) / (N - 1)) / 1000;
    RefractionModel::Input data{.ha = ha, .hs = x[j] * 1000, .R = R};
    y[j] = testModel.calculate_psi_g(data);
  }

  // pass data points to graphs:
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x, y);

  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()
