#include "calculateResult.h"

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

void calculateResult() {
  if (!isInputCorrect()) return;
  ExponentAtmosphericModel exponential_atmospheric_model;
  SegmentedAtmosphericModel segmented_atmospheric_model;
  switch (user_input_data.getTask()) {
    case (gui::Task::Forward):
      // set needed task;
      break;
    case (gui::Reversed):
      // set needed task
      break;
  }
  switch (user_input_data.getAtmosphericModel()) {
    case (gui::AtmosphericModel::GOST440481): {
    } break;
    case (gui::AtmosphericModel::Segmented): {
      SegmentedAtmosphericModel atmosphere(
          user_input_data.getHeightOfSurface(),
          user_input_data.getRefractiiveIndex());
      segmented_atmospheric_model = atmosphere;
      break;
    }
    case (gui::AtmosphericModel::Exponential): {
      ExponentAtmosphericModel atmosphere(
          user_input_data.getHeightOfSurface(),
          user_input_data.getRefractiiveIndex());
      exponential_atmospheric_model = atmosphere;

      break;
    }
  }
  RefractionModel::Input data{user_input_data.getStation(),
                              user_input_data.getTarget(),
                              user_input_data.getDistance()};
  switch (user_input_data.getRefractionModel()) {
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
        AverageKModel_forExponent average_k_model_for_exponent(
            exponential_atmospheric_model);
        answer = average_k_model_for_exponent.calculate(data);
      } else {
        if (user_input_data.getAtmosphericModel() ==
            gui::AtmosphericModel::Segmented) {
          // AverageKModel average_k_model(shared ptr ??);
        } else {
        }
      }
    } break;
    case (gui::RefractionModel::AverageRho):
      if (user_input_data.getCountingMethod() == gui::Integration) {
        AveragePModel_forExponent average_p_model_for_exponent(
            exponential_atmospheric_model);
        answer = average_p_model_for_exponent.calculate(data);
      } else {
        if (user_input_data.getAtmosphericModel() ==
            gui::AtmosphericModel::Segmented) {
          // AverageKModel average_p_model(shared ptr ??);
        } else {
        }
      }
      break;
  }
}
