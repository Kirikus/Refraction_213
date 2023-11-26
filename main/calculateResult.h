#ifndef CALCULATERESULT_H
#define CALCULATERESULT_H

#include "../lib/atmospheric_model.h"
#include "../lib/average_k_model.h"
#include "../lib/average_k_model_for_exponent.h"
#include "../lib/average_p_model.h"
#include "../lib/average_p_model_for_exponent.h"
#include "../lib/exponent_model.h"
#include "../lib/model4div3.h"
#include "../lib/model_without_refraction.h"
#include "../lib/segmented_atmosheric_model.h"
#include "data.h"

bool isInputCorrect();
void calculateResult();
extern RefractionModel::Answer answer;
#endif  // CALCULATERESULT_H
