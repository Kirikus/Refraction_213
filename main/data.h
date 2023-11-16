#ifndef DATA_H
#define DATA_H

#include <qcustomplot.h>

#include <cmath>
#include <string>

namespace gui {

enum Task { Forward, Reversed };
enum AtmosphericModel { GOST440481, Segmented, Numerical_Integration };
enum RefractionModel { Effective_Radius43, Geometric, AverageK, AverageRho };

class Data {
  double target_height = std::nan("1");
  double station_height = std::nan("1");
  double dist_to_target = std::nan("1");
  AtmosphericModel atmospheric_model = GOST440481;
  RefractionModel refraction_model = Geometric;
  Task task = Forward;

 public:
  QCustomPlot *plot = nullptr;
  Data(double station_height, double target_height, double dist_to_target,
       AtmosphericModel atmospheric_model, RefractionModel refraction_model,
       Task task);
  Data();
  void setPlot(QCustomPlot *plt);
  void setStation(double height);
  void setTarget(double height);
  void setDistance(double distance_from_station_to_target);
  void setAtmosphericModel(AtmosphericModel atmospheric_model);
  void setRefractionModel(RefractionModel refraction_model);
  void setTask(enum Task);
  double getStation();
  double getTarget();
  double getDistance();
};
}  // namespace gui
extern gui::Data user_input_data;

#endif
