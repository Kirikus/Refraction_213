#include "test_universal.h"

#include <QApplication>

#include "../lib/angle_calculator_for_exponent_model.h"
#include "../lib/average_k_model.h"
#include "../lib/average_k_model_for_exponent.h"
#include "../lib/average_p_model.h"
#include "../lib/average_p_model_for_exponent.h"
#include "../lib/exponent_model.h"
#include "../lib/iterative_algorithm.h"
#include "../lib/iterative_algorithm_for_exponent.h"
#include "../lib/model4div3.h"
#include "../lib/model_without_refraction.h"
#include "../lib/segmented_atmosheric_model.h"
#include "../lib/universal_angle_calculator.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

void testGraph(
    double graph_height, double step, double Ns, double R, double accu_1 = 0.01,
    double accu_2 =
        0.01) {  // accu - параметры, задающие точность в итеративном алгоритме
  int argc = 1;
  double hs = 0;
  char* argv[] = {"General tests"};

  QApplication a(argc, {});
  QCustomPlot customPlot;

  customPlot.legend->setVisible(true);
  std::shared_ptr<SegmentedAtmosphericModel> segm_model(
      new SegmentedAtmosphericModel(hs, Ns));
  std::shared_ptr<ExponentAtmosphericModel> exp_model(
      new ExponentAtmosphericModel(hs, Ns));
  QVector<double> test_it_data(graph_height + 10, 0);
  AverageKModel testAverageKModel(exp_model);
  const ExponentAtmosphericModel& exact_exp_model =
      ExponentAtmosphericModel(hs, Ns);
  std::shared_ptr<UniversalAngleCalculator> ang_calc_uni(
      new UniversalAngleCalculator(segm_model));
  IterativeAlgorithm test_it_alg(ang_calc_uni, accu_1, accu_2, 0.1);
  for (int ha = graph_height; ha > 1000; ha = ha - step) {
    EffectiveRadiusModel::Input data{double(ha), hs, R};
    test_it_data[ha] = (test_it_alg.calculate(data).psi_d);
  }
  customPlot.addGraph();
  customPlot.graph(0)->setName("Численное интегрирование с аппроксимацией");
  QVector<double> x_part, y_part;
  std::shared_ptr<AngleCalculatorForExponentModel> ang_calc_exp(
      new AngleCalculatorForExponentModel(exact_exp_model));
  IterativeAlgorithmForExponentModel test_it_alg_exp(ang_calc_exp, accu_1,
                                                     accu_2, 0.1);
  for (int ha = graph_height; ha > 900; ha = ha - step) {
    EffectiveRadiusModel::Input data{(double)ha, hs, R};
    y_part.push_back(ha);
    x_part.push_back(test_it_data[ha] - test_it_alg_exp.calculate(data).psi_d);
  }
  customPlot.graph(0)->setPen(QPen(Qt::darkCyan, 2));
  customPlot.graph(0)->setData(x_part, y_part, true);

  x_part.clear();
  y_part.clear();
  customPlot.addGraph();
  customPlot.graph(1)->setPen(QPen(Qt::red, 2));

  customPlot.graph(1)->setName("Геометрическая модель");
  ModelWithoutRefraction test_geom_model;
  for (int ha = graph_height; ha > 1000; ha = ha - step) {
    EffectiveRadiusModel::Input data{(double)ha, hs, R};
    y_part.push_back(ha);
    x_part.push_back(test_it_data[ha] - test_geom_model.calculate_psi_d(data));
  }
  customPlot.graph(1)->setPen(QPen(Qt::green, 2));
  customPlot.graph(1)->setData(x_part, y_part, true);

  x_part.clear();
  y_part.clear();
  customPlot.addGraph();
  customPlot.graph(2)->setName("Модель 4/3");
  Model4div3 test_model_4div3;
  for (int ha = graph_height; ha > 1000; ha = ha - step) {
    EffectiveRadiusModel::Input data{(double)ha, hs, R};
    y_part.push_back(ha);
    x_part.push_back(test_it_data[ha] - test_model_4div3.calculate(data).psi_d);
  }
  customPlot.graph(2)->setPen(QPen(Qt::red, 2));
  customPlot.graph(2)->setData(x_part, y_part, true);

  x_part.clear();
  y_part.clear();
  customPlot.addGraph();
  customPlot.graph(3)->setName("Модель среднего К с подстановкой");
  AverageKModel_forExponent test_average_k_exp(exact_exp_model);
  for (int ha = graph_height; ha > 1000; ha = ha - step) {
    EffectiveRadiusModel::Input data{(double)ha, hs, R};
    y_part.push_back(ha);
    x_part.push_back(test_it_data[ha] -
                     test_average_k_exp.calculate(data).psi_d);
  }
  customPlot.graph(3)->setPen(QPen(Qt::magenta, 2));
  customPlot.graph(3)->setData(x_part, y_part, true);

  x_part.clear();
  y_part.clear();
  customPlot.addGraph();
  AverageKModel test_average_k(segm_model);
  customPlot.graph(4)->setName("Модель среднего K");
  for (int ha = graph_height; ha > 1000; ha = ha - step) {
    EffectiveRadiusModel::Input data{(double)ha, hs, R};
    y_part.push_back(ha);
    x_part.push_back(test_it_data[ha] - test_average_k.calculate(data).psi_d);
  }
  customPlot.graph(4)->setPen(QPen(Qt::black, 2));
  customPlot.graph(4)->setData(x_part, y_part, true);

  x_part.clear();
  y_part.clear();
  customPlot.addGraph();
  customPlot.graph(5)->setPen(QPen(Qt::yellow, 2));

  customPlot.graph(5)->setName("Модель среднего Р");
  AveragePModel test_average_p(segm_model);
  for (int ha = graph_height; ha > 1000; ha = ha - step) {
    EffectiveRadiusModel::Input data{(double)ha, hs, R};
    y_part.push_back(ha);
    x_part.push_back(test_it_data[ha] - test_average_p.calculate(data).psi_d);
  }
  customPlot.graph(5)->setPen(QPen(Qt::blue, 2));
  customPlot.graph(5)->setData(x_part, y_part, true);

  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);
  customPlot.yAxis->scaleRange(1000, 1);
  customPlot.xAxis->scaleRange(0.001, 0);
  customPlot.xAxis->setLabel("Разность углов, рад");
  customPlot.yAxis->setLabel("Высота, м");
  customPlot.show();
  customPlot.resize(640, 480);
  a.exec();
}

BOOST_AUTO_TEST_SUITE(errors)

BOOST_AUTO_TEST_CASE(graph_errors_250_100) {
  testGraph(30000, 100, 250, 100000, 0.01, 0.01);
}

BOOST_AUTO_TEST_CASE(graph_errors_313_100) {
  testGraph(30000, 100, 313, 100000, 0.01, 0.01);
}

BOOST_AUTO_TEST_CASE(graph_errors_400_100) {
  testGraph(30000, 100, 400, 100000, 0.01, 0.01);
}

BOOST_AUTO_TEST_CASE(graph_errors_250_30) {
  testGraph(15000, 100, 250, 30000, 0.01, 0.01);
}

BOOST_AUTO_TEST_CASE(graph_errors_400_30) {
  testGraph(15000, 100, 400, 30000, 0.01, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()
