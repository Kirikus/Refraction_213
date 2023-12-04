#include <QApplication>

#include "../lib/average_p_model_for_exponent.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(d_avg_p_exp)

BOOST_AUTO_TEST_CASE(d_simple) {
  ExponentAtmosphericModel atmosphere(0, 313);
  AveragePModel_forExponent testModel(atmosphere);
  EffectiveRadiusModel::Input data{0, 2000, 2000};
  BOOST_TEST(testModel.calculate_d(M_PI / 3, M_PI / 6,
                                   reinterpret_cast<void *>(&data)) ==
                 4 / 3 * (Re + data.hs) * M_PI / 6,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(psi_d_avg_p_exp)

ExponentAtmosphericModel atmosphere(0, 313);
AveragePModel_forExponent testModel(atmosphere);

BOOST_AUTO_TEST_CASE(simple) {
  RefractionModel::Input data{.ha = 0, .hs = 0, .R = 0};
  BOOST_TEST(testModel.calculate_psi_d(data) == 0);
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
BOOST_AUTO_TEST_CASE(plot_for_p_avg) {
  // image 2.33
  int argc = 1;
  char *argv[] = {"p_avg"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  // bins for hs
  const int N = 100;
  const double h_min = 300, h_max = 3 * 10000;
  QVector<double> x(N), y(N);
  const double R = 30000;  // distance between target and radar
  const double hs = 0;     // high of target

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  customPlot.yAxis->setLabel("ha, km");
  customPlot.xAxis->setLabel("k_avg");

  for (int j = 0; j < N; ++j) {
    y[j] = (h_min + j * (h_max - h_min) / (N - 1));
    RefractionModel::Input data{.ha = y[j], .hs = hs, .R = R};
    x[j] = testModel.k(data);
  }

  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  customPlot.graph(0)->setData(x, y);
  customPlot.yAxis->setScaleType(QCPAxis::stLogarithmic);
  customPlot.yAxis->setRange(300, 30000);
  customPlot.xAxis->setRange(1.05, 1.4);
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()
