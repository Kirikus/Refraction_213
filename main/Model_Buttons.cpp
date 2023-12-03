#include "calculateResult.h"
#include "mainwindow.h"
// Сами функции, вызываемые при нажатии кнопок

void MainWindow::ExponentRefractiveIndexNearSurfaceEdit_textEdited(
    const QString& index) {
  user_input_data.setRefractiveIndex(index.QString::toDouble());
  calculateResult();
  showAnswer();
}

void MainWindow::ExponentHeightAboveTheSeaEdit_textEdited(
    const QString& height) {
  user_input_data.setHeightOfSurface(height.QString::toDouble());
  calculateResult();
  showAnswer();
}

void MainWindow::SegmentedRefractiveIndexNearSurfaceEdit_textEdited(
    const QString& index) {
  user_input_data.setRefractiveIndex(index.QString::toDouble());
  calculateResult();
  showAnswer();
}

void MainWindow::SegmentedHeightAboveTheSeaEdit_textEdited(
    const QString& height) {
  user_input_data.setHeightOfSurface(height.QString::toDouble());
  calculateResult();
  showAnswer();
}

void MainWindow::on_integrateButton_clicked() {
  user_input_data.setCountingMethod(gui::Integration);
  calculateResult();
  showAnswer();
}

void MainWindow::on_fittingButton_clicked() {
  user_input_data.setCountingMethod(gui::Fitting);
  calculateResult();
  showAnswer();
}
