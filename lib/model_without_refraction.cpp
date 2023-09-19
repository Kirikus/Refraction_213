#include "model_without_refraction.h"

double R_via_psi_d(double ha, double psi_d)
{
    double R = (Re + ha) * std::sin(psi_d) - std::sqrt(Re * Re - pow((Re + ha) * std::cos(psi_d), 2));
    return R;
}

double R_via_psi_g(double ha, double psi_g)
{
    double R = -Re * std::sin(psi_g) + std::sqrt(pow(Re * std::sin(psi_g), 2) + 2 * Re * ha + ha * ha);
    return R;
}

double d(double psi_d, double psi_g)
{
    double d = Re * (psi_d - psi_g);
    return d;
}
