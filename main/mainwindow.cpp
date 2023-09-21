#include "mainwindow.h"
#include "QMessageBox"
#include <iostream>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->stationCoordinatesEdit->setPlaceholderText("Координаты Станции");
  ui->targetCoordinatesEdit->setPlaceholderText("Координаты Цели");
  ui->distanceToTargetEdit->setPlaceholderText("Расстояние До Цели");

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_reverseTaskButton_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("reverse task");
    msg.setText("I was pushed");
    msg.exec();
}


void MainWindow::on_directTaskButton_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("direct task");
    msg.setText("I was pushed");
    msg.exec();
}

