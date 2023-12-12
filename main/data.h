#ifndef DATA_H
#define DATA_H

#include <qcustomplot.h>

#include <string>
#include <vector>

#include "../lib/refraction_model.h"

namespace gui {
enum CountingMethod { Fitting, Integration };
enum Task { Forward, Reversed };
enum InterpolationMethod { Linear, Spline };
enum class AtmosphericModel { GOST440481, Segmented, Exponential };
enum class RefractionModel {
  Effective_Radius43,
  Geometric,
  AverageK,
  AverageRho,
  GeometricLine,
  FittingAngle,
  IterativeAlgorithm
};

class Data {
  double target_height = std::nan("1");
  double station_height = std::nan("1");
  double dist_to_target = std::nan("1");

  double height_of_surface = std::nan("1");
  double refractive_index_near_surface = std::nan("1");

  std::vector<std::string> gost_temperature_data;
  std::vector<std::string> gost_pressure_data;

  double sliding_angle = std::nan("1");
  double declination_angle = std::nan("1");
  double distance_on_surface = std::nan("1");

  InterpolationMethod temperature_interpolation = Linear;
  InterpolationMethod pressure_interpolation = Linear;
  CountingMethod counting_method = Fitting;
  AtmosphericModel atmospheric_model = AtmosphericModel::Exponential;
  RefractionModel refraction_model = RefractionModel::Geometric;
  Task task = Forward;

 public:
  QCustomPlot* plot = nullptr;
  void setHeightOfSurface(double height);
  void setRefractiveIndex(double index);
  void setCountingMethod(CountingMethod method);
  void setPlot(QCustomPlot* plt);
  void setStation(double height);
  void setTarget(double height);
  void setDistance(double distance_from_station_to_target);
  void setAtmosphericModel(AtmosphericModel atmospheric_model);
  void setRefractionModel(RefractionModel refraction_model);
  void setTask(Task task);
  void setAnswer(::RefractionModel::Answer answer);
  void setGostTemperature(std::vector<std::string>& tmeperature);
  void setGostPressure(std::vector<std::string>& pressure);
  void setTemperatureInterpolationMethod(InterpolationMethod method);
  void setPressureInterpolationMethod(InterpolationMethod method);
  std::vector<std::string> getGostPressure();
  std::vector<std::string> getGostTemperature();
  double getSlidingAngle();
  double getDeclinationAngle();
  double getSurfaceDistance();
  double getStation();
  double getTarget();
  double getDistance();
  double getHeightOfSurface();
  double getRefractiiveIndex();
  InterpolationMethod getTemperatureInterpolatingMethod();
  InterpolationMethod getPressureInterpolatingMethod();
  CountingMethod getCountingMethod();
  AtmosphericModel getAtmosphericModel();
  RefractionModel getRefractionModel();
  Task getTask();
};
}  // namespace gui
extern gui::Data user_input_data;

#endif
