#include <QApplication>

#include "../lib/model_without_refraction.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(reverse_task)

ModelWithoutRefraction testModelRound;

BOOST_AUTO_TEST_CASE(simple) {
  RefractionModel::Input data{.ha = 0, .hs = 0, .R = 0};
  BOOST_TEST(testModelRound.calculate(data).d ==
                 testModelRound
                     .calculate_reverse_task(
                         data.ha, testModelRound.calculate(data).psi_d, data.R,
                         data.ha)
                     .d,
             tt::tolerance(1e-6));
  BOOST_TEST(data.hs == testModelRound
                            .calculate_reverse_task(
                                data.ha, testModelRound.calculate(data).psi_d,
                                data.R, data.ha)
                            .hs,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(vertical_line) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1000};
  BOOST_TEST(testModelRound.calculate(data).d ==
                 testModelRound
                     .calculate_reverse_task(
                         data.ha, testModelRound.calculate(data).psi_d, data.R,
                         data.hs)
                     .d,
             tt::tolerance(1e-6));
  BOOST_TEST(data.hs == testModelRound
                            .calculate_reverse_task(
                                data.ha, testModelRound.calculate(data).psi_d,
                                data.R, data.hs)
                            .hs,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(another_dots) {
  RefractionModel::Input data{.ha = 2000, .hs = 1000, .R = 1500};
  BOOST_TEST(testModelRound.calculate(data).d ==
                 testModelRound
                     .calculate_reverse_task(
                         data.ha, testModelRound.calculate(data).psi_d, data.R,
                         data.hs)
                     .d,
             tt::tolerance(1e-6));
  BOOST_TEST(data.hs == testModelRound
                            .calculate_reverse_task(
                                data.ha, testModelRound.calculate(data).psi_d,
                                data.R, data.hs)
                            .hs,
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()
