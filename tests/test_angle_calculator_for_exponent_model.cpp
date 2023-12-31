#include <QApplication>

#include "../lib/angle_calculator_for_exponent_model.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(exponent_angle)

#ifdef TEST_PLOTS

BOOST_AUTO_TEST_CASE(plot_2_34_d) {
  // Plot 2.34 from booklet
  int argc = 1;
  char *argv[] = {"difference of angles exponent psi_d"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  double hs = 0;
  double Ns = 313;
  ExponentAtmosphericModel atm(hs, Ns);
  AngleCalculatorForExponentModel testModel(atm);
  const int N = 100;
  const double h_min = 0, h_max = 30000;
  QVector<double> x(N), y(N);
  QVector<double> angles{M_PI / 6,   M_PI / 18,  M_PI / 60,
                         M_PI / 180, M_PI / 600, M_PI / 1800};
  for (int j = 0; j < angles.size(); ++j) {
    for (int i = 0; i < N; ++i) {
      y[i] = h_min + i * (h_max - h_min) / (N - 1);
      x[i] = abs(testModel.psi_d(y[i], hs, angles.at(j)) - angles.at(j)) * 180 /
             M_PI;
    }
    customPlot.graph(j)->setData(x, y);
    customPlot.addGraph();
  }

  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  customPlot.yAxis->setLabel("h, m");
  customPlot.xAxis->setLabel("|psi_d - psi_g|, degrees");

  customPlot.graph(angles.size() - 1)->rescaleAxes();

  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  customPlot.resize(640, 480);

  a.exec();
}
#endif

BOOST_AUTO_TEST_SUITE_END()
