#include "test_gost_model.h"

#include <QApplication>

#include "../lib/gostmodel.h"
#include "../lib/linearmodel.h"
#include "../lib/splinemodel.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
std::vector<std::string> data1 = {"1000;2", "2000;3", "3000;4", "5000;6"};
std::vector<std::string> data2 = {"1000;6", "2000;8", "3000;10", "4000;12"};

BOOST_AUTO_TEST_SUITE(opening_files_and_interpolation_test)

BOOST_AUTO_TEST_CASE(vector_string_gost_construction) {
  SplineModel* data_p = new SplineModel(data1);
  LinearModel* data_t = new LinearModel(data2);
  GOSTModel test_gost(data_p, data_t);
  BOOST_TEST(test_gost.Ro(1000) == 0.0057, tt::tolerance(0.01));
  BOOST_TEST(test_gost.N(1000) == 2602, tt::tolerance(1.0));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(graph_for_Ro_in_gost_model)

BOOST_AUTO_TEST_CASE(plot_for_random_dots_v2) {
  int argc = 1;
  char* argv[] = {"Test for density in GOSTModel"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::red));
  customPlot.yAxis->setLabel("h, m");
  customPlot.xAxis->setLabel("Ro, g/m^3");
  QVector<double> x_part, y_part;
  SplineModel* data_p = new SplineModel(data1);
  LinearModel* data_t = new LinearModel(data2);
  GOSTModel gost(data_p, data_t);
  for (int i = 12000; i > 0; i--) {
    y_part.push_back(i);
    x_part.push_back(gost.Ro(i));
  }
  customPlot.addGraph();
  customPlot.xAxis->setScaleType(QCPAxis::stLogarithmic);
  customPlot.yAxis->setRange(0, 12000);
  customPlot.xAxis->setRange(0.01 * 0.001, 10 * 0.001);
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
