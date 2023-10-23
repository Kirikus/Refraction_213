#include "mainwindow.h"
#include "data.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui -> stationCoordinatesEdit -> setValidator(new QDoubleValidator());
  ui -> targetCoordinatesEdit -> setValidator(new QDoubleValidator());
  ui -> distanceToTargetEdit -> setValidator(new QDoubleValidator());
  ui -> plot -> xAxis -> setRange(0, 10000);
  ui -> plot -> yAxis -> setRange(0, 10000);
  user_input_data.setPlot(ui -> plot);
  
}

MainWindow::~MainWindow() { delete ui; }

