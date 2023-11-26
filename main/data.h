#ifndef DATA_H
#define DATA_H

#include <qcustomplot.h>

#include <cmath>
#include <map>
#include <string>

namespace gui {
enum CountingMethod { Fitting, Integration };
enum Task { Forward, Reversed };
enum class AtmosphericModel { GOST440481, Segmented, Exponential };
enum class RefractionModel {
  Effective_Radius43,
  Geometric,
  AverageK,
  AverageRho
};

class Data {
  double target_height = std::nan("1");
  double station_height = std::nan("1");
  double dist_to_target = std::nan("1");
  double height_of_surface = std::nan("1");
  double refractive_index_near_surface = std::nan("1");
  CountingMethod counting_method = Fitting;
  AtmosphericModel atmospheric_model = AtmosphericModel::GOST440481;
  RefractionModel refraction_model = RefractionModel::Geometric;
  Task task = Forward;

 public:
  QCustomPlot *plot = nullptr;
  Data(double station_height, double target_height, double dist_to_target,
       AtmosphericModel atmospheric_model, RefractionModel refraction_model,
       Task task);
  Data();
  void setHeightOfSurface(double height);
  void setRefractiveIndex(double index);
  void setCountingMethod(CountingMethod method);
  void setPlot(QCustomPlot *plt);
  void setStation(double height);
  void setTarget(double height);
  void setDistance(double distance_from_station_to_target);
  void setAtmosphericModel(AtmosphericModel atmospheric_model);
  void setRefractionModel(RefractionModel refraction_model);
  void setTask(Task task);
  double getStation();
  double getTarget();
  double getDistance();
  double getHeightOfSurface();
  double getRefractiiveIndex();
  CountingMethod getCountingMethod();
  AtmosphericModel getAtmosphericModel();
  RefractionModel getRefractionModel();
  Task getTask();
};
}  // namespace gui
extern gui::Data user_input_data;

#endif
