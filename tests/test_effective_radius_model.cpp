#include "test_effective_radius_model.h"

#include <QApplication>

#include "../lib/effective_radius_model.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(R_effective_radius)

EffectiveRadiusModel testEffectiveRadiusModel;

BOOST_AUTO_TEST_CASE(ground_level_psi_d) {
  BOOST_TEST(testEffectiveRadiusModel.R_via_psi_d(0, 0, 0) == 0,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(ground_level_psi_g) {
  BOOST_TEST(testEffectiveRadiusModel.R_via_psi_g(0, 0, 0) == 0,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(ha_2000m) {
  BOOST_TEST(testEffectiveRadiusModel.R_via_psi_d(2000, 0, M_PI / 2) == 2000,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(ha_8000m) {
  BOOST_TEST(testEffectiveRadiusModel.R_via_psi_g(8000, 2000, M_PI / 2) == 6000,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(psi_g_0) {
  BOOST_TEST(testEffectiveRadiusModel.R_via_psi_g(2000, 0, 0) ==
                 std::sqrt(pow(2000 + Re, 2) - Re * Re),
             tt::tolerance(1e-6));
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
      y[j] = testEffectiveRadiusModel.R_via_psi_d(x[j], 0, psi);
    }
    // pass data points to graphs:
    customPlot.addGraph();
    customPlot.graph(i)->setPen(QPen(Qt::blue));
    customPlot.graph(i)->setData(x, y);
  }
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
      y[j] = testEffectiveRadiusModel.R_via_psi_g(x[j], 0, psi);
    }
    // pass data points to graphs:
    customPlot.addGraph();
    customPlot.graph(i)->setPen(QPen(Qt::blue));
    customPlot.graph(i)->setData(x, y);
  }
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

BOOST_AUTO_TEST_SUITE(d_effective_radius)

EffectiveRadiusModel testEffectiveRadiusModel;

BOOST_AUTO_TEST_CASE(d_simple) {
  double hs = 2000;
  BOOST_TEST(testEffectiveRadiusModel.d(M_PI / 3, M_PI / 6,
                                        reinterpret_cast<void *>(&hs)) ==
                 4 / 3 * (Re + hs) * M_PI / 6,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(psi_d_effective_radius)

EffectiveRadiusModel testEffectiveRadiusModel;

BOOST_AUTO_TEST_CASE(simple) {
  BOOST_TEST(testEffectiveRadiusModel.psi_d(0, 0, 0) == 0);
}

BOOST_AUTO_TEST_CASE(equilateral_triangle) {
  BOOST_TEST(testEffectiveRadiusModel.psi_d(2000, 2000, Re + 2000) == M_PI / 6,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(psi_d_pi_2) {
  BOOST_TEST(testEffectiveRadiusModel.psi_d(2000, 1000, 1000) == M_PI / 2,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(same_dote) {
  BOOST_TEST(testEffectiveRadiusModel.psi_d(2000, 2000, 0) == 0,
             tt::tolerance(1e-6));
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
    y[j] = testEffectiveRadiusModel.psi_d(ha, x[j] * 1000, R);
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

BOOST_AUTO_TEST_SUITE(psi_g_effective_radius)

EffectiveRadiusModel testEffectiveRadiusModel;

BOOST_AUTO_TEST_CASE(simple) {
  BOOST_TEST(testEffectiveRadiusModel.psi_g(0, 0, 0) == 0);
}

BOOST_AUTO_TEST_CASE(equilateral_triangle) {
  BOOST_TEST(testEffectiveRadiusModel.psi_g(2000, 2000, Re + 2000) == -M_PI / 6,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(psi_g_pi_2) {
  BOOST_TEST(testEffectiveRadiusModel.psi_g(2000, 1000, 1000) == M_PI / 2,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(same_dote) {
  BOOST_TEST(testEffectiveRadiusModel.psi_g(2000, 2000, 0) == 0,
             tt::tolerance(1e-6));
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
    y[j] = testEffectiveRadiusModel.psi_g(ha, x[j] * 1000, R);
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

BOOST_AUTO_TEST_SUITE(phi_e_effective_radius)

EffectiveRadiusModel testEffectiveRadiusModel;

BOOST_AUTO_TEST_CASE(simple) {
  BOOST_TEST(testEffectiveRadiusModel.phi_e_via_distances(0, 0, 0) == 0);
}

BOOST_AUTO_TEST_CASE(equilateral_triangle) {
  BOOST_TEST(testEffectiveRadiusModel.phi_e_via_distances(
                 2000, 2000, Re + 2000) == M_PI / 3,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(same_dote) {
  BOOST_TEST(testEffectiveRadiusModel.phi_e_via_distances(2000, 2000, 0) == 0,
             tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_for_phi_e) {
  int argc = 1;
  char *argv[] = {"phi_e"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  // bins for hs
  const int N = 100;
  const double h_min = 1000, h_max = 3 * 100000;
  QVector<double> x(N), y(N);
  const double hs = 1000;  // high of target
  const double ha = 1000;  // high of radar

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.xAxis->setLabel("R, 100 km");
  customPlot.yAxis->setLabel("phi_e, radians");

  for (int j = 0; j < N; ++j) {
    x[j] = (h_min + j * (h_max - h_min) / (N - 1)) / 100000;
    y[j] = testEffectiveRadiusModel.phi_e_via_distances(ha, hs, x[j] * 100000);
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

BOOST_AUTO_TEST_SUITE(hs_via_psi_d_effective_radius)

EffectiveRadiusModel testEffectiveRadiusModel;

BOOST_AUTO_TEST_CASE(ground_level_psi_d) {
  BOOST_TEST(testEffectiveRadiusModel.hs_via_psi_d(0, 0, 0) == 0);
}

BOOST_AUTO_TEST_CASE(equilateral_triangle) {
  BOOST_TEST(
      testEffectiveRadiusModel.hs_via_psi_d(2000, M_PI / 6, Re + 2000) == 2000,
      tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(psi_d_90) {
  BOOST_TEST(
      testEffectiveRadiusModel.hs_via_psi_d(2000, M_PI / 2, 1000) == 1000,
      tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_for_hs_via_psi_d) {
  int argc = 1;
  char *argv[] = {"hs_via_psi_d"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  // bins for high
  const int N = 1000;
  const double ha_min = -100, ha_max = 3 * 100000;
  // bins for angles
  const int M = 6;
  const double psi_min = 0, psi_max = M_PI / 2;
  const double R = 1000;  // distance between target and radar
  QVector<double> x(N), y(N);

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.xAxis->setLabel("ha, km");
  customPlot.yAxis->setLabel("hs, km");

  for (int i = 0; i < M; ++i) {
    double psi = psi_min + i * (psi_max - psi_min) / (M - 1);
    for (int j = 0; j < N; ++j) {
      x[j] = ha_min + j * (ha_max - ha_min) / (N - 1) / 1000;
      y[j] = testEffectiveRadiusModel.hs_via_psi_d(x[j] * 1000, psi, R) / 1000;
    }
    // pass data points to graphs:
    customPlot.addGraph();
    customPlot.graph(i)->setPen(QPen(Qt::blue));
    customPlot.graph(i)->setData(x, y);
  }
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
