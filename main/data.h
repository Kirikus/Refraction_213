#ifndef DATA_H
#define DATA_H

#include <string>

#include "qcustomplot.h"

class Data {
  int target_coords = 0;
  int station_coords = 0;
  int dist_to_target = 0;
  std::string atmosphere_model = "Не выбрано";
  std::string refraction_model = "Не выбрано";
  std::string task = "Прямая задача";
  public:
    QCustomPlot * plot = nullptr;
  Data(int station_coords, int target_coords, int dist_to_target, std::string atmosphere_model, std::string refraction_model, std::string task);
  Data();
  void setPlot(QCustomPlot * plt);
  void setStCoords(int station_coords);
  void setTrgCoords(int target_coords);
  void setDstToTarget(int target_distance);
  void setAtmosphereModel(std::string atmosphere_model);
  void setRefractionModel(std::string refraction_model);
  void setTask(std::string task);
  int getStCoords();
  int getTrgCoords();
  int getDstToTarget();
};

#endif
