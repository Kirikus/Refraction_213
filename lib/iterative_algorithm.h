#ifndef ITERATIVEALGORITHM_H
#define ITERATIVEALGORITHM_H
#include <vector>
using std::vector;

#include "refraction_aware_model.h"

class IterativeAlgorithm : public RefractionAwareModel
{
public:
 virtual Answer calculate(const Input &data, void *opaque = nullptr) override;
 IterativeAlgorithm(std::shared_ptr<AngleCalculator> angle_difference_algorithm, double, double);

private:
 double delta_psi_g = 0.1;
 double mu = 1;
 double G(const Input&, double);
 double eps0 = 1;
};
#endif // ITERATIVEALGORITHM_H
