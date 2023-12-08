#include "calculateResult.h"

#include <memory>

#include "../lib/atmospheric_model.h"
#include "../lib/average_k_model.h"
#include "../lib/average_k_model_for_exponent.h"
#include "../lib/average_p_model.h"
#include "../lib/average_p_model_for_exponent.h"
#include "../lib/exponent_model.h"
#include "../lib/geometric_model_line.h"
#include "../lib/model4div3.h"
#include "../lib/model_without_refraction.h"
#include "../lib/segmented_atmosheric_model.h"
#include "data.h"

RefractionModel::Answer answer;

bool isInputCorrect() {
  if (!(user_input_data.getDistance() - abs(user_input_data.getTarget() -
                                            user_input_data.getStation()) >=
            0 &&
        !std::isnan(user_input_data.getTarget()) &&
        !std::isnan(user_input_data.getStation())))
    return false;
  return true;
}

void chooseAtmosphericModel(std::shared_ptr<AtmosphericModel> atmosphere) {
  switch (user_input_data.getAtmosphericModel()) {
    case (gui::AtmosphericModel::GOST440481): {
    } break;
    case (gui::AtmosphericModel::Segmented): {
      atmosphere = std::make_shared<SegmentedAtmosphericModel>(
          SegmentedAtmosphericModel(user_input_data.getHeightOfSurface(),
                                    user_input_data.getRefractiiveIndex()));
      break;
    }
    case (gui::AtmosphericModel::Exponential): {
      atmosphere = std::make_shared<ExponentAtmosphericModel>(
          ExponentAtmosphericModel(user_input_data.getHeightOfSurface(),
                                   user_input_data.getRefractiiveIndex()));
      break;
    }
  }
}

void chooseRefractionModel(std::shared_ptr<AtmosphericModel> atmosphere) {
  RefractionModel::Input data{user_input_data.getStation(),
                              user_input_data.getTarget(),
                              user_input_data.getDistance()};
  switch (user_input_data.getRefractionModel()) {
    case (gui::RefractionModel::GeometricLine): {
      GeometricModelLine lineModel;
      answer = lineModel.calculate(data);
      break;
    }
    case (gui::RefractionModel::Effective_Radius43): {
      Model4div3 model4div3;
      answer = model4div3.calculate(data);
      break;
    }
    case (gui::RefractionModel::Geometric): {
      ModelWithoutRefraction model_without_refraction;
      answer = model_without_refraction.calculate(data);
      break;
    }
    case (gui::RefractionModel::AverageK): {
      if (user_input_data.getCountingMethod() == gui::Integration) {
        if (ExponentAtmosphericModel* exponent_atmosphere =
                dynamic_cast<ExponentAtmosphericModel*>(atmosphere.get())) {
          AverageKModel_forExponent average_k_model_for_exponent(
              *exponent_atmosphere);
          answer = average_k_model_for_exponent.calculate(data);
        }
      } else {
        if (user_input_data.getAtmosphericModel() ==
            gui::AtmosphericModel::Segmented) {
          AverageKModel average_k_model(atmosphere);
          answer = average_k_model.calculate(data);
        } else {
          // add options for GOST
        }
      }
    } break;
    case (gui::RefractionModel::AverageRho):
      if (user_input_data.getCountingMethod() == gui::Integration) {
        if (ExponentAtmosphericModel* exponent_atmosphere =
                dynamic_cast<ExponentAtmosphericModel*>(atmosphere.get())) {
          AveragePModel_forExponent average_p_model_for_exponent(
              *exponent_atmosphere);
          answer = average_p_model_for_exponent.calculate(data);
        }
      } else {
        if (user_input_data.getAtmosphericModel() ==
            gui::AtmosphericModel::Segmented) {
          AverageKModel average_k_model(atmosphere);
          answer = average_k_model.calculate(data);
        } else {
          // add options for GOST
        }
      }
      break;
  }
}

void calculateResult() {
  if (!isInputCorrect()) return;
  switch (user_input_data.getTask()) {
    case (gui::Task::Forward):
      // set needed task;
      break;
    case (gui::Reversed):
      // set needed task
      break;
  }
  std::shared_ptr<AtmosphericModel> atmosphere;
  chooseAtmosphericModel(atmosphere);
  chooseRefractionModel(atmosphere);
}
