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

private slots:
  void on_stationCoordinatesEdit_textEdited(const QString &arg1);

  void on_targetCoordinatesEdit_textEdited(const QString &arg1);

  void on_distanceToTargetEdit_textEdited(const QString &arg1);

  void on_directTaskButton_clicked();

  void on_reverseTaskButton_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
