#include "data.h"

#include "mainwindow.h"

#include "QMessageBox"

#include "plotting.h"

#include "parsing.h"

void MainWindow::on_reverseTaskButton_clicked() {
  QMessageBox msg;
  msg.setWindowTitle("reverse task");
  msg.setText("I was pushed");
  msg.exec();
}

void MainWindow::on_directTaskButton_clicked() {
  QMessageBox msg;
  msg.setWindowTitle("direct task");
  msg.setText("I was pushed");
  msg.exec();
}

void MainWindow::on_distanceToTargetEdit_textEdited(
    const QString &dst_to_target) {
  user_input_data.setDistance(parse_double(dst_to_target.toStdString()));
  addTargetAndStation();
}

void MainWindow::on_targetCoordinatesEdit_textEdited(
    const QString &trg_height) {
  user_input_data.setTarget(parse_double(trg_height.toStdString()));
  addTargetAndStation();
}

void MainWindow::on_stationCoordinatesEdit_textEdited(
    const QString &st_height) {
  user_input_data.setStation(parse_double(st_height.toStdString()));
  addTargetAndStation();
}
