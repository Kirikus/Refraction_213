#ifndef DATA_H
#define DATA_H

#include <string>

#include "qcustomplot.h"

enum Task { Forward, Reversed };
enum AtmosphereModel { GOST440481, Segmented, Numerical_Integration };
enum RefractionModel { Effective_Radius43, Geometric, AverageK, AverageRho };

class Data {
  double target_height = 0;
  double station_height = 0;
  double dist_to_target = 0;
  AtmosphereModel atmosphere_model = GOST440481;
  RefractionModel refraction_model = Geometric;
  Task task = Forward;

public:
  QCustomPlot *plot = nullptr;
  Data(double station_height, double target_height, double dist_to_target,
       AtmosphereModel atmosphere_model, RefractionModel refraction_model, Task task);
  Data();
  void setPlot(QCustomPlot *plt);
  void setStation(double height);
  void setTarget(double height);
  void setDistance(double distance_from_station_to_target);
  void setAtmosphereModel(AtmosphereModel atmosphere_model);
  void setRefractionModel(RefractionModel refraction_model);
  void setTask(enum Task);
  double getStation();
  double getTarget();
  double getDistance();
};

extern Data user_input_data;

#endif
