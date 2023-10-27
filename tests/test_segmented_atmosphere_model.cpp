#include "test_segmented_atmosphere_model.h"

#include <QApplication>

#include "../lib/segmented_atmosheric_model.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_N)

SegmentedAtmosphericModel testModel;

BOOST_AUTO_TEST_CASE(ground_level) {
  BOOST_TEST(testModel.N(0) == 324.8, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_1000m) {
  BOOST_TEST(testModel.N(1000 - 1e-6) == testModel.N(1000 + 1e-6),
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_9000m) {
  BOOST_TEST(testModel.N(9000 - 1e-6) == testModel.N(9000 + 1e-6),
             tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_2_32) {
  // Plot 2.32 from booklet
  int argc = 1;
  char *argv[] = {"N(h)"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  testModel = SegmentedAtmosphericModel(0, 400);
  customPlot.graph(0)->setPen(QPen(Qt::red));
  const int N = 1000;
  const double h_min = 0, h_max = 15000;
  QVector<double> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    y[i] = h_min + i * (h_max - h_min) / (N - 1);
    x[i] = testModel.N(y[i]);
  }
  // pass data points to graphs:
  customPlot.graph(0)->setData(x, y);

  customPlot.addGraph();
  testModel = SegmentedAtmosphericModel(0, 313);
  customPlot.graph(1)->setPen(QPen(Qt::green));
  for (int i = 0; i < N; ++i) {
    y[i] = h_min + i * (h_max - h_min) / (N - 1);
    x[i] = testModel.N(y[i]);
  }
  // pass data points to graphs:
  customPlot.graph(1)->setData(x, y);

  customPlot.addGraph();
  testModel = SegmentedAtmosphericModel(0, 250);
  customPlot.graph(2)->setPen(QPen(Qt::blue));
  for (int i = 0; i < N; ++i) {
    y[i] = h_min + i * (h_max - h_min) / (N - 1);
    x[i] = testModel.N(y[i]);
  }
  // pass data points to graphs:
  customPlot.graph(2)->setData(x, y);

  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.yAxis->setLabel("h, m");
  customPlot.xAxis->setLabel("N, n/u");
  // let the ranges scale themselves so graph 0 fits perfectly in the visible
  // area:
  customPlot.graph(0)->rescaleAxes();
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
