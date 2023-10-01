#include "test_model_without_refraction.h"

#include <QApplication>

#include "../lib/model_without_refraction.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(R)

BOOST_AUTO_TEST_CASE(ground_level_psi_d) { BOOST_TEST(R_via_psi_d(0, 0) == 0); }

BOOST_AUTO_TEST_CASE(ground_level_psi_g) { BOOST_TEST(R_via_psi_g(0, 0) == 0); }

BOOST_AUTO_TEST_CASE(ha_2000m) {
  BOOST_TEST(R_via_psi_d(2000, M_PI/2) == 2000, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(ha_8000m) {
  BOOST_TEST(R_via_psi_g(2000, M_PI/2) == 2000, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(psi_g_0) {
  BOOST_TEST(R_via_psi_g(2000, 0) == std::sqrt(pow(2000+Re, 2) - Re*Re), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(d_simple) {
  BOOST_TEST(d(M_PI/3, M_PI/6) == Re * M_PI/6, tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_for_R_via_psi_d) {
  int argc = 1;
  char *argv[] = {"R_via_psi_d"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  // bins for high
  const int N = 1000;
  const double ha_min = -10000, ha_max = 3 * 1000000;
  // bins for angles
  const int M = 6;
  const double psi_min = 0, psi_max = M_PI / 2;
  QVector<double> x(N), y(N);

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.xAxis->setLabel("ha, m");
  customPlot.yAxis->setLabel("R, m");

  for (int i = 0; i < M; ++i) {
      double psi = psi_min + i * (psi_max - psi_min) / (M - 1);
      for (int j = 0; j < N; ++j) {
        x[j] = ha_min + j * (ha_max - ha_min) / (N - 1);
        y[j] = R_via_psi_d(x[j], psi);
        // pass data points to graphs:
        customPlot.addGraph();
        customPlot.graph(i)->setPen(QPen(Qt::blue));
        customPlot.graph(i)->setData(x, y);
      }
    }
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

BOOST_AUTO_TEST_CASE(plot_for_R_via_psi_g) {
  int argc = 1;
  char *argv[] = {"R_via_psi_g"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  // bins for high
  const int N = 1000;
  const double ha_min = -10000, ha_max = 3 * 1000000;
  // bins for angles
  const int M = 6;
  const double psi_min = 0, psi_max = M_PI / 2;
  QVector<double> x(N), y(N);

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.xAxis->setLabel("ha, m");
  customPlot.yAxis->setLabel("R, m");

  for (int i = 0; i < M; ++i) {
      double psi = psi_min + i * (psi_max - psi_min) / (M - 1);
      for (int j = 0; j < N; ++j) {
        x[j] = ha_min + j * (ha_max - ha_min) / (N - 1);
        y[j] = R_via_psi_g(x[j], psi);
        // pass data points to graphs:
        customPlot.addGraph();
        customPlot.graph(i)->setPen(QPen(Qt::blue));
        customPlot.graph(i)->setData(x, y);
      }
    }
  // Note: we could have also just called customPlot->rescaleAxes(); instead
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
