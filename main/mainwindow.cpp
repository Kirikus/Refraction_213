#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "data.h"
#include "doubleValidator.h"

constexpr double max_distance = 12800000;
constexpr double max_height = 50000;
constexpr double max_decimals = 5;

std::map<std::string, gui::AtmosphericModel> string_to_atmospheric_model = {
    {"Модель ГОСТ4401-81", gui::AtmosphericModel::GOST440481},
    {"Сегментированная модель", gui::AtmosphericModel::Segmented},
    {"Экспоненциальная модель", gui::AtmosphericModel::Exponential}};
std::map<std::string, gui::RefractionModel> string_to_refraction_model = {
    {"Модель эффективного радиуса 4/3",
     gui::RefractionModel::Effective_Radius43},
    {"Геометрическая модель", gui::RefractionModel::Geometric},
    {"Модель среднего K", gui::RefractionModel::AverageK},
    {"Модель среднего P", gui::RefractionModel::AverageRho}};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->stationCoordinatesEdit->setValidator(new betterDoubleValidator(
      0, max_height, max_decimals, ui->stationCoordinatesEdit));
  ui->targetCoordinatesEdit->setValidator(new betterDoubleValidator(
      0, max_height, max_decimals, ui->targetCoordinatesEdit));
  ui->distanceToTargetEdit->setValidator(new betterDoubleValidator(
      0, max_distance, max_decimals, ui->distanceToTargetEdit));
  ui->plot->xAxis->setRange(0, 10000);
  ui->plot->yAxis->setRange(0, 10000);
  ui->plot->setInteraction(
      QCP::iRangeZoom, true);  // Включаем взаимодействие удаления/приближения
  ui->plot->setInteraction(
      QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
  user_input_data.setPlot(ui->plot);
}

MainWindow::~MainWindow() { delete ui; }
