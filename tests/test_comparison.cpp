#include "test_comparison.h"

#include <QApplication>

#include "../lib/angle_calculator_for_exponent_model.h"
#include "../lib/effective_radius_model.h"
#include "../lib/fitting_algorithm.h"
#include "../lib/iterative_algorithm.h"
#include "../lib/segmented_atmosheric_model.h"
#include "../lib/universal_angle_calculator.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_difference_of_algorithms)
void testGraph(
    double graph_height, double step, double Ns, double R, double accu_1 = 0.01,
    double accu_2 =
        0.01) {  // accu - параметры, задающие точность в итеративном алгоритме
  int argc = 1;
  double hs = 0;
  char* argv[] = {"General tests"};

  QApplication a(argc, {});
  QCustomPlot customPlot;
  customPlot.addGraph();
  QVector<double> x_part, y_part;
  std::shared_ptr<SegmentedAtmosphericModel> segm_model(
      new SegmentedAtmosphericModel(hs, Ns));
  std::shared_ptr<UniversalAngleCalculator> ang_calc_uni(
      new UniversalAngleCalculator(segm_model));
  QVector<double> test_it_data(graph_height + 10, 0);
  FittingAlgorithm test_fit_alg(ang_calc_uni, graph_height, hs);
  QVector<double> test_fit_data(graph_height + 10, 0);
  IterativeAlgorithm test_it_alg(ang_calc_uni, accu_1, accu_2, 0.1);
  for (int ha = graph_height; ha > 1000; ha = ha - step) {
    EffectiveRadiusModel::Input data{double(ha), hs, R};
    test_it_data[ha] = (test_it_alg.calculate(data).psi_d);
    test_fit_data[ha] = (test_fit_alg.calculate(data).psi_d);
  }
  for (int ha = graph_height; ha > 900; ha = ha - step) {
    y_part.push_back(ha);
    x_part.push_back((test_it_data[ha] - test_fit_data[ha]) * 180 / M_PI);
  }
  customPlot.graph(0)->setPen(QPen(Qt::blue, 2));
  customPlot.graph(0)->setData(x_part, y_part, true);

  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);
  customPlot.yAxis->scaleRange(1000, 1);
  customPlot.xAxis->scaleRange(0.001, 0);
  customPlot.xAxis->setLabel("Разность углов, градусы");
  customPlot.yAxis->setLabel("Высота, м");
  customPlot.show();
  customPlot.resize(640, 480);
  a.exec();
}

BOOST_AUTO_TEST_CASE(graph_for_iterative_and_fitting) {
  testGraph(30000, 100, 250, 100000, 0.01, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()
