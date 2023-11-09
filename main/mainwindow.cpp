#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "data.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->stationCoordinatesEdit->setValidator(
      new QDoubleValidator(ui->stationCoordinatesEdit));
  ui->targetCoordinatesEdit->setValidator(
      new QDoubleValidator(ui->targetCoordinatesEdit));
  ui->distanceToTargetEdit->setValidator(
      new QDoubleValidator(ui->distanceToTargetEdit));
  ui->plot->xAxis->setRange(0, 10000);
  ui->plot->yAxis->setRange(0, 10000);
  ui->plot->setInteraction(
      QCP::iRangeZoom, true);  // Включаем взаимодействие удаления/приближения
  ui->plot->setInteraction(
      QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
  user_input_data.setPlot(ui->plot);
}

MainWindow::~MainWindow() { delete ui; }
