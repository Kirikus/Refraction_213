#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "data.h"
#include "doubleValidator.h"

constexpr double max_distance = 12800000;
constexpr double max_height = 50000;
constexpr double max_decimals = 5;

MainWindow::MainWindow(QWidget *parent)
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
