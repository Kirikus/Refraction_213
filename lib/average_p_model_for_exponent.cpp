#include "average_p_model_for_exponent.h"

double AveragePModel_forExponent::k(const RefractionModel::Input &data) {
  ExponentAtmosphericModel atmosphere;
  ModelWithoutRefraction approximate;
  double Hb = atmosphere.get_Hb();
  double Ns = atmosphere.get_Ns();
  double psi_g = approximate.calculate_psi_g(data);
  double k_avg = 1 / (1 - pow(10, -6) * Ns * std::cos(psi_g) * Re / Hb *
                              (data.ha - data.hs) / Hb /
                              (exp((data.ha - data.hs) / Hb) - 1));

  return k_avg;
}
