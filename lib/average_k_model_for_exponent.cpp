#include "average_k_model_for_exponent.h"

double AverageKModel_forExponent::k(const RefractionModel::Input &data) {
  ModelWithoutRefraction approximate;
  double Hb = atmosphere.get_Hb();
  double Ns = atmosphere.get_Ns();
  double psi_g = approximate.calculate_psi_g(data);
  double k_avg = Hb / (data.ha - data.hs) *
                 log((exp((data.ha - data.hs) / Hb) -
                      pow(10, -6) * Ns * std::cos(psi_g) * Re / Hb) /
                     (1 - pow(10, -6) * Ns * std::cos(psi_g) * Re / Hb));
  return k_avg;
}
