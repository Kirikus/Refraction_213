#include "calculateResult.h"

#include <memory>

#include "../lib/atmospheric_model.h"
#include "../lib/average_k_model.h"
#include "../lib/average_k_model_for_exponent.h"
#include "../lib/average_p_model.h"
#include "../lib/average_p_model_for_exponent.h"
#include "../lib/exponent_model.h"
#include "../lib/geometric_model_line.h"
#include "../lib/gostmodel.h"
#include "../lib/linearmodel.h"
#include "../lib/model4div3.h"
#include "../lib/model_without_refraction.h"
#include "../lib/segmented_atmosheric_model.h"
#include "../lib/splinemodel.h"
#include "data.h"

RefractionModel::Answer answer;

std::shared_ptr<AtmosphericModel> atmosphere;

bool isInputCorrect() {
  if (!(user_input_data.getDistance() - abs(user_input_data.getTarget() -
                                            user_input_data.getStation()) >=
            0 &&
        !std::isnan(user_input_data.getTarget()) &&
        !std::isnan(user_input_data.getStation())))
    return false;
  return true;
}

void chooseAtmosphericModel() {
  switch (user_input_data.getAtmosphericModel()) {
    case (gui::AtmosphericModel::GOST440481): {
      std::vector<std::string> temperature =
          user_input_data.getGostTemperature();
      std::vector<std::string> pressure = user_input_data.getGostPressure();
      if (temperature.size() == 0 || pressure.size() == 0) break;
      FunctionModel1D* data_t = nullptr;
      FunctionModel1D* data_p = nullptr;
      switch (user_input_data.getTemperatureInterpolatingMethod()) {
        case (gui::Spline): {
          data_t = new SplineModel(temperature);
          break;
        }
        case (gui::Linear): {
          data_t = new LinearModel(temperature);
          break;
        }
      }
      switch (user_input_data.getPressureInterpolatingMethod()) {
        case (gui::Spline): {
          data_p = new SplineModel(pressure);
          break;
        }
        case (gui::Linear): {
          data_p = new LinearModel(pressure);
          break;
        }
      }
      auto gost_atmosphere =
          std::make_shared<GOSTModel>(GOSTModel(data_p, data_t));
      atmosphere = std::dynamic_pointer_cast<AtmosphericModel>(gost_atmosphere);
      break;
    }
    case (gui::AtmosphericModel::Segmented): {
      auto segmented_atmosphere = std::make_shared<SegmentedAtmosphericModel>(
          SegmentedAtmosphericModel(user_input_data.getHeightOfSurface(),
                                    user_input_data.getRefractiiveIndex()));
      qDebug() << typeid(segmented_atmosphere).name() << "CAS";
      atmosphere =
          std::dynamic_pointer_cast<AtmosphericModel>(segmented_atmosphere);

      qDebug() << typeid(atmosphere).name() << "ATM";
      break;
    }
    case (gui::AtmosphericModel::Exponential): {
      auto exponent_atmosphere = std::make_shared<ExponentAtmosphericModel>(
          ExponentAtmosphericModel(user_input_data.getHeightOfSurface(),
                                   user_input_data.getRefractiiveIndex()));
      atmosphere =
          std::dynamic_pointer_cast<AtmosphericModel>(exponent_atmosphere);

      qDebug() << typeid(atmosphere).name();

      break;
    }
  }
}

void chooseRefractionModel() {
  RefractionModel::Input data{user_input_data.getStation(),
                              user_input_data.getTarget(),
                              user_input_data.getDistance()};
  qDebug() << typeid(atmosphere).name();
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
        AverageKModel average_k_model(atmosphere);
        answer = average_k_model.calculate(data);
      }
    } break;
    case (gui::RefractionModel::AverageRho): {
      if (user_input_data.getCountingMethod() == gui::Integration) {
        if (ExponentAtmosphericModel* exponent_atmosphere =
                dynamic_cast<ExponentAtmosphericModel*>(atmosphere.get())) {
          AveragePModel_forExponent average_p_model_for_exponent(
              *exponent_atmosphere);
          answer = average_p_model_for_exponent.calculate(data);
        }
      } else {
        AveragePModel average_p_model(atmosphere);
        answer = average_p_model.calculate(data);
      }
      break;
    }
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

  chooseAtmosphericModel();
  chooseRefractionModel();
}
