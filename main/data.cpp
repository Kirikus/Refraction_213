#include "data.h"

Data user_input_data = Data();

Data::Data(int station_coords, int target_coords, int dist_to_target, std::string atmosphere_model, std::string refraction_model, std::string task) {
  this -> station_coords = station_coords;
  this -> target_coords = target_coords;
  this -> dist_to_target = dist_to_target;
  this -> atmosphere_model = atmosphere_model;
  this -> refraction_model = refraction_model;
  this -> task = task;
}
Data::Data() {
  this -> station_coords = -1;
  this -> target_coords = -1;
  this -> dist_to_target = -1;
  this -> atmosphere_model = "Не выбрано";
  this -> refraction_model = "Не выбрано";
  this -> task = "Прямая задача";
}
void Data::setDstToTarget(int dist) {
  this -> dist_to_target = dist;
}
void Data::setPlot(QCustomPlot * plt) {
  this -> plot = plt;
}

void Data::setStCoords(int station_coords) {
  this -> station_coords = station_coords;
}
void Data::setTrgCoords(int target_coords) {
  this -> target_coords = target_coords;
}
int Data::getDstToTarget() {
  return this -> dist_to_target;
}
int Data::getTrgCoords() {
  return this -> target_coords;
}

int Data::getStCoords() {
  return this -> station_coords;
}
