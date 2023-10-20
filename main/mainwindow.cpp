#include "mainwindow.h"
#include "data.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->stationCoordinatesEdit->setPlaceholderText("100");
  ui->targetCoordinatesEdit->setPlaceholderText("1000");
  ui->distanceToTargetEdit->setPlaceholderText("1400");
  ui -> stationCoordinatesEdit -> setValidator(new QIntValidator());
  ui -> targetCoordinatesEdit -> setValidator(new QIntValidator());
  ui -> distanceToTargetEdit -> setValidator(new QIntValidator());
  ui -> plot -> xAxis -> setRange(0, 10000);
  ui -> plot -> yAxis -> setRange(0, 10000);
  user_input_data.setPlot(ui -> plot);
  
}

MainWindow::~MainWindow() { delete ui; }

