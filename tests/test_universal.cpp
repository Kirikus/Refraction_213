#include "test_universal.h"

#include "../lib/average_k_model.h"
#include "../lib/model4div3.h"
#include "../lib/average_p_model.h"
#include "../lib/iterative_algorithm.h"
#include "../lib/iterative_algorithm_for_exponent.h"
#include "../lib/exponent_model.h"
#include "../lib/iterative_algorithm.h"
#include "../lib/universal_angle_calculator.h"
#include "../lib/average_k_model_for_exponent.h"
#include "../lib/average_p_model_for_exponent.h"
#include <QApplication>
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(errors)

BOOST_AUTO_TEST_CASE(making_graphs_250){
    int argc = 1;
    char *argv[] = {"Test for difference of angles (Ns = 250, R = 100)"};
    QApplication a(argc, argv);

    QCustomPlot customPlot;
    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::red));

    std::shared_ptr<ExponentAtmosphericModel> atmosphere(
        new ExponentAtmosphericModel(0, 250));
    AverageKModel testAverageKModel(atmosphere);

    std::shared_ptr<UniversalAngleCalculator> AngCalc(new UniversalAngleCalculator(atmosphere));
    IterativeAlgorithm testItAlg(AngCalc, 0.1, 0.1);
    QVector<double> x_part, y_part;
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAverageKModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(0)->setPen(QPen(Qt::green));
    customPlot.graph(0)->setData(x_part, y_part);

//     Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  //   graphs by clicking:

    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(1)->setPen(QPen(Qt::red));

    AveragePModel testAveragePModel(atmosphere);

    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAveragePModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(1)->setLineStyle(QCPGraph::lsNone);
     customPlot.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(1)->setPen(QPen(Qt::blue));
    customPlot.graph(1)->setData(x_part, y_part);


    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(2)->setPen(QPen(Qt::red));

    Model4div3 testModel4div3;

    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testModel4div3.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(2)->setPen(QPen(Qt::red));
    customPlot.graph(2)->setData(x_part, y_part);
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);



    customPlot.addGraph();
    x_part.clear();
    y_part.clear();

    const ExponentAtmosphericModel& atmosphere2 = ExponentAtmosphericModel(0, 250);
    AverageKModel_forExponent testAverageK2(atmosphere2);
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageK2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);


    AveragePModel_forExponent testAverageP2(atmosphere2);
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageP2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);
    customPlot.show();
    customPlot.resize(640, 480);
    a.exec();
}

BOOST_AUTO_TEST_CASE(making_graphs_313){
    int argc = 1;
    char *argv[] = {"Test for difference of angles(Ns = 313, R = 100)"};
    QApplication a(argc, argv);

    QCustomPlot customPlot;
    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::red));

    std::shared_ptr<ExponentAtmosphericModel> atmosphere(
        new ExponentAtmosphericModel(0, 313));
    AverageKModel testAverageKModel(atmosphere);

    std::shared_ptr<UniversalAngleCalculator> AngCalc(new UniversalAngleCalculator(atmosphere));
    IterativeAlgorithm testItAlg(AngCalc, 0.1, 0.1);
    QVector<double> x_part, y_part;
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAverageKModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(0)->setPen(QPen(Qt::green));
    customPlot.graph(0)->setData(x_part, y_part);

//     Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  //   graphs by clicking:

    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(1)->setPen(QPen(Qt::red));

    AveragePModel testAveragePModel(atmosphere);

    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAveragePModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(1)->setLineStyle(QCPGraph::lsNone);
     customPlot.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(1)->setPen(QPen(Qt::blue));
    customPlot.graph(1)->setData(x_part, y_part);


    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(2)->setPen(QPen(Qt::red));

    Model4div3 testModel4div3;

    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testModel4div3.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(2)->setPen(QPen(Qt::red));
    customPlot.graph(2)->setData(x_part, y_part);
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);



    customPlot.addGraph();
    x_part.clear();
    y_part.clear();

    const ExponentAtmosphericModel& atmosphere2 = ExponentAtmosphericModel(0, 313);
    AverageKModel_forExponent testAverageK2(atmosphere2);
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageK2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);


    AveragePModel_forExponent testAverageP2(atmosphere2);
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageP2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);
    customPlot.show();
    customPlot.resize(640, 480);
    a.exec();
}


BOOST_AUTO_TEST_CASE(making_graphs_400){
    int argc = 1;
    char *argv[] = {"Test for difference of angles(Ns = 400, R = 100)"};
    QApplication a(argc, argv);

    QCustomPlot customPlot;
    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::red));

    std::shared_ptr<ExponentAtmosphericModel> atmosphere(
        new ExponentAtmosphericModel(0, 400));
    AverageKModel testAverageKModel(atmosphere);

    std::shared_ptr<UniversalAngleCalculator> AngCalc(new UniversalAngleCalculator(atmosphere));
    IterativeAlgorithm testItAlg(AngCalc, 0.1, 0.1);
    QVector<double> x_part, y_part;
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAverageKModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(0)->setPen(QPen(Qt::green));
    customPlot.graph(0)->setData(x_part, y_part);

//     Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  //   graphs by clicking:

    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(1)->setPen(QPen(Qt::red));

    AveragePModel testAveragePModel(atmosphere);

    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAveragePModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(1)->setLineStyle(QCPGraph::lsNone);
     customPlot.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(1)->setPen(QPen(Qt::blue));
    customPlot.graph(1)->setData(x_part, y_part);


    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(2)->setPen(QPen(Qt::red));

    Model4div3 testModel4div3;

    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testModel4div3.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(2)->setPen(QPen(Qt::red));
    customPlot.graph(2)->setData(x_part, y_part);
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);



    customPlot.addGraph();
    x_part.clear();
    y_part.clear();

    const ExponentAtmosphericModel& atmosphere2 = ExponentAtmosphericModel(0, 400);
    AverageKModel_forExponent testAverageK2(atmosphere2);
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageK2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);


    AveragePModel_forExponent testAverageP2(atmosphere2);
    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageP2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);
    customPlot.show();
    customPlot.resize(640, 480);
    a.exec();
}

BOOST_AUTO_TEST_CASE(making_graphs_250_v2){
    int argc = 1;
    char *argv[] = {"Test for difference of angles(Ns = 250, R = 30)"};
    QApplication a(argc, argv);

    QCustomPlot customPlot;
    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::red));

    std::shared_ptr<ExponentAtmosphericModel> atmosphere(
        new ExponentAtmosphericModel(0, 250));
    AverageKModel testAverageKModel(atmosphere);

    std::shared_ptr<UniversalAngleCalculator> AngCalc(new UniversalAngleCalculator(atmosphere));
    IterativeAlgorithm testItAlg(AngCalc, 0.1, 0.1);
    QVector<double> x_part, y_part;
    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAverageKModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(0)->setPen(QPen(Qt::green));
    customPlot.graph(0)->setData(x_part, y_part);

//     Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  //   graphs by clicking:

    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(1)->setPen(QPen(Qt::red));

    AveragePModel testAveragePModel(atmosphere);

    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAveragePModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(1)->setLineStyle(QCPGraph::lsNone);
     customPlot.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(1)->setPen(QPen(Qt::blue));
    customPlot.graph(1)->setData(x_part, y_part);


    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(2)->setPen(QPen(Qt::red));

    Model4div3 testModel4div3;

    for (int ha = 30000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testModel4div3.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(2)->setPen(QPen(Qt::red));
    customPlot.graph(2)->setData(x_part, y_part);
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);



    customPlot.addGraph();
    x_part.clear();
    y_part.clear();

    const ExponentAtmosphericModel& atmosphere2 = ExponentAtmosphericModel(0, 250);
    AverageKModel_forExponent testAverageK2(atmosphere2);
    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageK2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);


    AveragePModel_forExponent testAverageP2(atmosphere2);
    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 100000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageP2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);
    customPlot.show();
    customPlot.resize(640, 480);
    a.exec();
}

BOOST_AUTO_TEST_CASE(making_graphs_400_v2){
    int argc = 1;
    char *argv[] = {"Test for difference of angles(Ns = 400, R = 30)"};
    QApplication a(argc, argv);

    QCustomPlot customPlot;
    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::red));

    std::shared_ptr<ExponentAtmosphericModel> atmosphere(
        new ExponentAtmosphericModel(0, 400));
    AverageKModel testAverageKModel(atmosphere);

    std::shared_ptr<UniversalAngleCalculator> AngCalc(new UniversalAngleCalculator(atmosphere));
    IterativeAlgorithm testItAlg(AngCalc, 0.1, 0.1);
    QVector<double> x_part, y_part;
    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAverageKModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(0)->setPen(QPen(Qt::green));
    customPlot.graph(0)->setData(x_part, y_part);

//     Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  //   graphs by clicking:

    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(1)->setPen(QPen(Qt::red));

    AveragePModel testAveragePModel(atmosphere);

    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d - testAveragePModel.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(1)->setLineStyle(QCPGraph::lsNone);
     customPlot.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(1)->setPen(QPen(Qt::blue));
    customPlot.graph(1)->setData(x_part, y_part);


    customPlot.addGraph();
    x_part.clear();
    y_part.clear();
    customPlot.graph(2)->setPen(QPen(Qt::red));

    Model4div3 testModel4div3;

    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testModel4div3.calculate(data).psi_d);
      }
    customPlot.addGraph();
    customPlot.graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(2)->setPen(QPen(Qt::red));
    customPlot.graph(2)->setData(x_part, y_part);
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);



    customPlot.addGraph();
    x_part.clear();
    y_part.clear();

    const ExponentAtmosphericModel& atmosphere2 = ExponentAtmosphericModel(0, 400);
    AverageKModel_forExponent testAverageK2(atmosphere2);
    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageK2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);


    AveragePModel_forExponent testAverageP2(atmosphere2);
    for (int ha = 15000; ha > 1000; ha = ha - 100) {
        EffectiveRadiusModel::Input data{(double)ha, 0, 30000};
        y_part.push_back(ha);
        testAverageKModel.calculate(data);
        x_part.push_back(testItAlg.calculate(data).psi_d +
                         -testAverageP2.calculate(data).psi_d);
      }
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);
    customPlot.addGraph();
    customPlot.graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    customPlot.graph(3)->setPen(QPen(Qt::magenta));
    customPlot.graph(3)->setData(x_part, y_part);
    customPlot.show();
    customPlot.resize(640, 480);
    a.exec();
}

BOOST_AUTO_TEST_SUITE_END()


