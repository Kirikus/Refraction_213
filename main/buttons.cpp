#include <QMessageBox>

#include "data.h"
#include "mainwindow.h"
#include "plotting.h"

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
  user_input_data.setDistance(dst_to_target.toDouble());
  calculateAndShow();
}

void MainWindow::on_targetCoordinatesEdit_textEdited(
    const QString &trg_height) {
  user_input_data.setTarget(trg_height.toDouble());
  calculateAndShow();
}

void MainWindow::on_stationCoordinatesEdit_textEdited(
    const QString &st_height) {
  user_input_data.setStation(st_height.toDouble());
  calculateAndShow();
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  switch (index) {
    case 0: {
      user_input_data.setTask(gui::Task::Forward);
      break;
    }
    case 1: {
      user_input_data.setTask(gui::Task::Reversed);
      break;
    }
  }
}
