#include "mainwindow.h"

#include <QLocale>

#include "./ui_mainwindow.h"
#include "calculateResult.h"

constexpr double min_height = -500;
constexpr double max_distance = 1000000;
constexpr double max_height = 15000;
constexpr double max_decimals = 5;
constexpr double max_surface_height = 20000;
constexpr double max_refractive_index = 2000;
constexpr double max_effective_radius_coefficient = 10;
constexpr double min_effective_radius_coefficient = 0.1;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto* stationCoordinatesValidator = new betterDoubleValidator(
      min_height, max_height, max_decimals, ui->stationCoordinatesEdit);
  stationCoordinatesValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));
  ui->stationCoordinatesEdit->setValidator(stationCoordinatesValidator);

  auto* targetCoordinatesValidator = new betterDoubleValidator(
      min_height, max_height, max_decimals, ui->stationCoordinatesEdit);
  targetCoordinatesValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));
  ui->targetCoordinatesEdit->setValidator(targetCoordinatesValidator);

  auto* distanceCoordinatesValidator = new betterDoubleValidator(
      0, max_distance, max_decimals, ui->distanceToTargetEdit);
  distanceCoordinatesValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));
  ui->distanceToTargetEdit->setValidator(distanceCoordinatesValidator);

  ui->plot->xAxis->setRange(0, 10000);
  ui->plot->yAxis->setRange(0, 10000);
  ui->plot->setInteraction(
      QCP::iRangeZoom, true);  // Включаем взаимодействие удаления/приближения
  ui->plot->setInteraction(
      QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
  user_input_data.setPlot(ui->plot);
}

MainWindow::~MainWindow() { delete ui; }
