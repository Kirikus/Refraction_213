#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Section.h"
#include "data.h"
#include "doubleValidator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  QLineEdit *SegmentedHeightAboveTheSeaEdit;
  QLineEdit *SegmentedRefractiveIndexNearSurfaceEdit;
  QLineEdit *ExponentHeightAboveTheSeaEdit;
  QLineEdit *ExponentRefractiveIndexNearSurfaceEdit;
  QRadioButton *averagekIntegrateButton;
  QRadioButton *averagepIntegrateButton;
  QRadioButton *averagekFittingButton;
  QRadioButton *averagepFittingButton;
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void showAnswer();

 private slots:
  void on_refractionModelBox_currentIndexChanged(const QString &arg1);

  void on_atmosphericModelBox_currentIndexChanged(const QString &arg1);

  void on_stationCoordinatesEdit_textEdited(const QString &arg1);

  void ExponentRefractiveIndexNearSurfaceEdit_textEdited(const QString &arg1);

  void ExponentHeightAboveTheSeaEdit_textEdited(const QString &arg1);

  void SegmentedRefractiveIndexNearSurfaceEdit_textEdited(const QString &arg1);

  void SegmentedHeightAboveTheSeaEdit_textEdited(const QString &arg1);

  void on_targetCoordinatesEdit_textEdited(const QString &arg1);

  void on_distanceToTargetEdit_textEdited(const QString &arg1);

  void on_directTaskButton_clicked();

  void on_reverseTaskButton_clicked();

  void on_integrateButton_clicked();

  void on_fittingButton_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
