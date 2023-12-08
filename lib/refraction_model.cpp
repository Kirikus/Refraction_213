#include "refraction_model.h"

RefractionModel::AnswerReverseTask RefractionModel::calculate_reverse_task(
    double ha, double psi_d, double R, double hs) {
  Input data{.ha = ha, .hs = hs, .R = R};
  double dh = ha / 100;
  while (true) {
    auto res = calculate(data);
    if (abs(res.psi_d - psi_d) <= std::pow(10, -3))
      return AnswerReverseTask{.hs = data.hs, .d = calculate(data).d};
    if (calculate(data).psi_d > psi_d) data.hs += dh;
    if (calculate(data).psi_d < psi_d) data.hs -= dh;

    if (calculate(Input{.ha = ha, .hs = hs + dh, .R = R}).psi_d < psi_d &&
            calculate(data).psi_d > psi_d ||
        calculate(Input{.ha = ha, .hs = hs - dh, .R = R}).psi_d > psi_d &&
            calculate(data).psi_d < psi_d)
      return AnswerReverseTask{.hs = data.hs, .d = calculate(data).d};
  }
}
