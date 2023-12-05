#include <QApplication>

#include "../lib/geometric_model_line.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(geometric_model_line)

GeometricModelLine testModel;

BOOST_AUTO_TEST_CASE(simple) {
  RefractionModel::Input data{.ha = 0, .hs = 0, .R = 0};
  RefractionModel::Answer answer{.psi_d = 0, .psi_g = 0, .d = 0};
  BOOST_TEST(testModel.calculate(data).psi_d == answer.psi_d,
             tt::tolerance(1e-6));
  BOOST_TEST(testModel.calculate(data).psi_g == answer.psi_g,
             tt::tolerance(1e-6));
  BOOST_TEST(testModel.calculate(data).d == answer.d, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(line) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1000};
  RefractionModel::Answer answer{.psi_d = M_PI / 2, .psi_g = M_PI / 2, .d = 0};
  BOOST_TEST(testModel.calculate(data).psi_d == answer.psi_d,
             tt::tolerance(1e-6));
  BOOST_TEST(testModel.calculate(data).psi_g == answer.psi_g,
             tt::tolerance(1e-6));
  BOOST_TEST(testModel.calculate(data).d == answer.d, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(isosceles_triangle) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1414.21356};
  RefractionModel::Answer answer{
      .psi_d = M_PI / 4, .psi_g = M_PI / 4, .d = 1000};

  BOOST_TEST(testModel.calculate(data).psi_d == answer.psi_d,
             tt::tolerance(1e-6));
  BOOST_TEST(testModel.calculate(data).psi_g == answer.psi_g,
             tt::tolerance(1e-6));
  BOOST_TEST(testModel.calculate(data).d == answer.d, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()
