#include "data.h"

Data user_input_data = Data();

Data::Data(double station_height, double target_height, double dist_to_target,
           AtmosphereModel atmosphere_model, RefractionModel refraction_model,
           Task task) {
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
  this->atmosphere_model = GOST440481;
  this->refraction_model = Geometric;
  this->task = Forward;
}
void Data::setDistance(double distance_from_station_to_target) {
  this->dist_to_target = distance_from_station_to_target;
}
void Data::setPlot(QCustomPlot *plot) { this->plot = plot; }

void Data::setStation(double height) { this->station_height = height; }
void Data::setTarget(double height) { this->target_height = height; }
double Data::getDistance() { return this->dist_to_target; }
double Data::getTarget() { return this->target_height; }

double Data::getStation() { return this->station_height; }
