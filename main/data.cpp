#include "data.h"

using namespace gui;

Data user_input_data = Data();

Data::Data(double station_height, double target_height, double dist_to_target,
           AtmosphericModel atmospheric_model, RefractionModel refraction_model,
           Task task) {
  this->station_height = station_height;
  this->target_height = target_height;
  this->dist_to_target = dist_to_target;
  this->atmospheric_model = atmospheric_model;
  this->refraction_model = refraction_model;
  this->task = task;
}

Data::Data() {
  this->station_height = std::nan("1");
  this->target_height = std::nan("1");
  this->dist_to_target = std::nan("1");
  this->height_of_surface = std::nan("1");
  this->refractive_index_near_surface = std::nan("1");
  this->counting_method = Fitting;
  this->atmospheric_model = AtmosphericModel::Exponential;
  this->refraction_model = RefractionModel::Geometric;
  this->task = Forward;
}

void Data::setDistance(double distance_from_station_to_target) {
  this->dist_to_target = distance_from_station_to_target;
}

void Data::setPlot(QCustomPlot *plot) { this->plot = plot; }

void Data::setStation(double height) { this->station_height = height; }

void Data::setTarget(double height) { this->target_height = height; }

void Data::setAtmosphericModel(AtmosphericModel atmospheric_model) {
  this->atmospheric_model = atmospheric_model;
}

void Data::setRefractionModel(RefractionModel refraction_model) {
  this->refraction_model = refraction_model;
}

void Data::setTask(enum Task task) { this->task = task; }

void Data::setHeightOfSurface(double height) {
  this->height_of_surface = height;
}

void Data::setRefractiveIndex(double index) {
  this->refractive_index_near_surface = index;
}

void Data::setCountingMethod(CountingMethod method) {
  this->counting_method = method;
}
double Data::getDistance() { return this->dist_to_target; }

double Data::getTarget() { return this->target_height; }

double Data::getStation() { return this->station_height; }

double Data::getHeightOfSurface() { return this->height_of_surface; }

double Data::getRefractiiveIndex() {
  return this->refractive_index_near_surface;
}
AtmosphericModel Data::getAtmosphericModel() { return this->atmospheric_model; }

RefractionModel Data::getRefractionModel() { return this->refraction_model; }

CountingMethod Data::getCountingMethod() { return counting_method; }

Task Data::getTask() { return this->task; }
