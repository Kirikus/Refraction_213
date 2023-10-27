#include "data.h"

Data user_input_data = Data();

Data::Data(double station_height, double target_height, double dist_to_target,
           std::string atmosphere_model, std::string refraction_model,
           std::string task) {
  this->station_height = station_height;
  this->target_height = target_height;
  this->dist_to_target = dist_to_target;
  this->atmosphere_model = atmosphere_model;
  this->refraction_model = refraction_model;
  this->task = task;
}
Data::Data() {
  this->station_height = -1;
  this->target_height = -1;
  this->dist_to_target = -1;
  this->atmosphere_model = "Не выбрано";
  this->refraction_model = "Не выбрано";
  this->task = "Прямая задача";
}
void Data::setDstToTarget(double dist) { this->dist_to_target = dist; }
void Data::setPlot(QCustomPlot *plt) { this->plot = plt; }

void Data::setStCoords(double station_height) {
  this->station_height = station_height;
}
void Data::setTrgCoords(double target_height) {
  this->target_height = target_height;
}
double Data::getDstToTarget() { return this->dist_to_target; }
double Data::getTrgCoords() { return this->target_height; }

double Data::getStCoords() { return this->station_height; }

