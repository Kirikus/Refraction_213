#ifndef DATA_H
#define DATA_H

#include <string>

#include "qcustomplot.h"

enum Task{
  Forward,
  Reversed
};

class Data {
  double target_height = 0;
  double station_height = 0;
  double dist_to_target = 0;
  std::string atmosphere_model = "Не выбрано";
  std::string refraction_model = "Не выбрано";
  Task task = Forward;

public:
  QCustomPlot *plot = nullptr;
  Data(double station_height, double target_height, double dist_to_target,
       std::string atmosphere_model, std::string refraction_model,
       Task task);
  Data();
  void setPlot(QCustomPlot *plt);
  void setStation(double height);
  void setTarget(double height);
  void setDistance(double distance_from_station_to_target);
  void setAtmosphereModel(std::string atmosphere_model);
  void setRefractionModel(std::string refraction_model);
  void setTask(enum Task);
  double getStation();
  double getTarget();
  double getDistance();
};

extern Data user_input_data;

#endif

