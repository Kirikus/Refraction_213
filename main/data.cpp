#include "data.h"

Data user_input_data = Data();

Data::Data(double station_coords, double target_coords, double dist_to_target,
           std::string atmosphere_model, std::string refraction_model,
           std::string task) {
  this->station_coords = station_coords;
  this->target_coords = target_coords;
  this->dist_to_target = dist_to_target;
  this->atmosphere_model = atmosphere_model;
  this->refraction_model = refraction_model;
  this->task = task;
}
Data::Data() {
  this->station_coords = -1;
  this->target_coords = -1;
  this->dist_to_target = -1;
  this->atmosphere_model = "Не выбрано";
  this->refraction_model = "Не выбрано";
  this->task = "Прямая задача";
}
void Data::setDstToTarget(double dist) { this->dist_to_target = dist; }
void Data::setPlot(QCustomPlot *plt) { this->plot = plt; }

void Data::setStCoords(double station_coords) {
  this->station_coords = station_coords;
}
void Data::setTrgCoords(double target_coords) {
  this->target_coords = target_coords;
}
double Data::getDstToTarget() { return this->dist_to_target; }
double Data::getTrgCoords() { return this->target_coords; }

double Data::getStCoords() { return this->station_coords; }

