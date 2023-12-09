#include "data.h"

using namespace gui;

Data user_input_data;

void Data::setDistance(double distance_from_station_to_target) {
  this->dist_to_target = distance_from_station_to_target;
}

void Data::setPlot(QCustomPlot* plot) { this->plot = plot; }

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

void Data::setGostTemperature(std::vector<std::string>& temperature) {
  this->gost_temperature_data = temperature;
}
void Data::setGostPressure(std::vector<std::string>& pressure) {
  this->gost_pressure_data = pressure;
}
std::vector<std::string> Data::getGostPressure() {
  return this->gost_temperature_data;
}
std::vector<std::string> Data::getGostTemperature() {
  return this->gost_pressure_data;
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

gui::RefractionModel Data::getRefractionModel() {
  return this->refraction_model;
}

CountingMethod Data::getCountingMethod() { return counting_method; }

void Data::setAnswer(::RefractionModel::Answer answer) {
  this->sliding_angle = answer.psi_g;
  this->declination_angle = answer.psi_d;
  this->distance_on_surface = answer.d;
}

double Data::getSlidingAngle() { return this->sliding_angle; }

double Data::getDeclinationAngle() { return this->declination_angle; }

double Data::getSurfaceDistance() { return this->distance_on_surface; }

void Data::setTemperatureInterpolationMethod(InterpolationMethod method) {
  this->temperature_interpolation = method;
}
void Data::setPressureInterpolationMethod(InterpolationMethod method) {
  this->pressure_interpolation = method;
}

InterpolationMethod Data::getTemperatureInterpolatingMethod() {
  return this->getTemperatureInterpolatingMethod();
}
InterpolationMethod Data::getPressureInterpolatingMethod() {
  return this->getPressureInterpolatingMethod();
}

Task Data::getTask() { return this->task; }
