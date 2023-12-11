#include <QApplication>

#include "../lib/average_p_model.h"
#include "../lib/segmented_atmosheric_model.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(d_avg_p)

BOOST_AUTO_TEST_CASE(d_simple) {
  std::shared_ptr<SegmentedAtmosphericModel> atmosphere(
      new SegmentedAtmosphericModel(0, 313));
  AveragePModel testAveragePModel(atmosphere);
  EffectiveRadiusModel::Input data{0, 2000, 2000};
  BOOST_TEST(testAveragePModel.calculate_d(M_PI / 3, M_PI / 6, data) ==
                 4 / 3 * (Re + data.hs) * M_PI / 6,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(psi_d_avg_p)

std::shared_ptr<SegmentedAtmosphericModel> atmosphere(
    new SegmentedAtmosphericModel(0, 313));
;
AveragePModel testAveragePModel(atmosphere);

BOOST_AUTO_TEST_CASE(simple) {
  RefractionModel::Input data{.ha = 0, .hs = 0, .R = 0};
  BOOST_TEST(testAveragePModel.calculate_psi_d(data) == 0);
}

BOOST_AUTO_TEST_CASE(psi_d_pi_2) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1000};
  BOOST_TEST(testAveragePModel.calculate_psi_d(data) == M_PI / 2,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(same_dote) {
  RefractionModel::Input data{.ha = 2000, .hs = 2000, .R = 0};
  BOOST_TEST(testAveragePModel.calculate_psi_d(data) == 0, tt::tolerance(1e-6));
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

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  customPlot.xAxis->setLabel("hs, km");
  customPlot.yAxis->setLabel("psi_d, radians");

  for (int j = 0; j < N; ++j) {
    x[j] = (h_min + j * (h_max - h_min) / (N - 1)) / 1000;
    RefractionModel::Input data{.ha = ha, .hs = x[j] * 1000, .R = R};
    y[j] = testAveragePModel.calculate_psi_d(data);
  }

  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x, y);

  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(psi_g_average_p)

std::shared_ptr<SegmentedAtmosphericModel> atmosphere(
    new SegmentedAtmosphericModel(0, 313));
AveragePModel testAveragePModel(atmosphere);

BOOST_AUTO_TEST_CASE(simple) {
  RefractionModel::Input data{.ha = 0, .hs = 0, .R = 0};
  BOOST_TEST(testAveragePModel.calculate_psi_g(data) == 0);
}

BOOST_AUTO_TEST_CASE(psi_g_pi_2) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1000};
  BOOST_TEST(testAveragePModel.calculate_psi_g(data) == M_PI / 2,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(same_dote) {
  RefractionModel::Input data{.ha = 2000, .hs = 2000, .R = 0};
  BOOST_TEST(testAveragePModel.calculate_psi_g(data) == 0, tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_for_P_avg) {
  int argc = 1;
  char *argv[] = {"p_avg"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  const int N = 100;
  const double h_min = 1000, h_max = 3 * 10000;
  QVector<double> x(N), y(N);
  const double hs = 0;

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  customPlot.xAxis->setLabel("p_avg");
  customPlot.yAxis->setLabel("ha, km");

  for (int j = 0; j < N; ++j) {
    y[j] = (h_min + j * (h_max - h_min) / (N - 1)) / 1000;
    EffectiveRadiusModel::Input data{y[j], hs, y[j] + 10 * j};
    x[j] = testAveragePModel.k(data);
  }

  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x, y);

  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()
