#include "mainwindow.h"

#include <QLocale>

#include "./ui_mainwindow.h"
#include "calculateResult.h"

constexpr double min_height = -500;
constexpr double max_distance = 1000000;
constexpr double max_height = 15000;
constexpr double max_decimals = 5;
constexpr double max_surface_height = 20000;
constexpr double max_refractive_index = 2000;
constexpr double max_effective_radius_coefficient = 10;
constexpr double min_effective_radius_coefficient = 0.1;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto* stationCoordinatesValidator = new betterDoubleValidator(
      min_height, max_height, max_decimals, ui->stationCoordinatesEdit);
  stationCoordinatesValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));
  ui->stationCoordinatesEdit->setValidator(stationCoordinatesValidator);

  auto* targetCoordinatesValidator = new betterDoubleValidator(
      min_height, max_height, max_decimals, ui->stationCoordinatesEdit);
  targetCoordinatesValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));
  ui->targetCoordinatesEdit->setValidator(targetCoordinatesValidator);

  auto* distanceCoordinatesValidator = new betterDoubleValidator(
      0, max_distance, max_decimals, ui->distanceToTargetEdit);
  distanceCoordinatesValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));
  ui->distanceToTargetEdit->setValidator(distanceCoordinatesValidator);

  ui->plot->xAxis->setRange(0, 10000);
  ui->plot->yAxis->setRange(0, 10000);
  ui->plot->setInteraction(
      QCP::iRangeZoom, true);  // Включаем взаимодействие удаления/приближения
  ui->plot->setInteraction(
      QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
  user_input_data.setPlot(ui->plot);
  ui::Section* section_segmented_model =
      new ui::Section("Параметры", 300, this, false, ModelType::Atmospheric);
  auto* segmented_model_layout = new QGridLayout();
  segmented_model_layout->addWidget(new QLabel(
      "Высота поверхности над уровнем моря:", section_segmented_model));

  SegmentedHeightAboveTheSeaEdit = new QLineEdit(this);

  auto* SegmentedHeightAboveTheSeaEditValidator = new betterDoubleValidator(
      0, max_surface_height, max_decimals, SegmentedHeightAboveTheSeaEdit);
  SegmentedHeightAboveTheSeaEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));

  SegmentedHeightAboveTheSeaEdit->setValidator(
      SegmentedHeightAboveTheSeaEditValidator);
  segmented_model_layout->addWidget(SegmentedHeightAboveTheSeaEdit, 0, 1);
  segmented_model_layout->addWidget(new QLabel(
      "Показатель преломления у поверхности:", section_segmented_model));
  SegmentedRefractiveIndexNearSurfaceEdit = new QLineEdit(this);

  auto* SegmentedRefractiveIndexNearSurfaceEditValidator =
      new betterDoubleValidator(0, max_refractive_index, max_decimals,
                                SegmentedRefractiveIndexNearSurfaceEdit);
  SegmentedRefractiveIndexNearSurfaceEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));

  SegmentedRefractiveIndexNearSurfaceEdit->setValidator(
      SegmentedRefractiveIndexNearSurfaceEditValidator);
  segmented_model_layout->addWidget(SegmentedRefractiveIndexNearSurfaceEdit, 1,
                                    1);
  section_segmented_model->setContentLayout(*segmented_model_layout);
  ui->atmosphericStackedWidget->insertWidget(0, section_segmented_model);

  ui::Section* section_exponential_model =
      new ui::Section("Параметры", 300, this, false, ModelType::Atmospheric);
  auto* exponential_model_layout = new QGridLayout();
  exponential_model_layout->addWidget(new QLabel(
      "Высота поверхности над уровнем моря:", section_exponential_model));

  ExponentHeightAboveTheSeaEdit = new QLineEdit(this);

  auto* ExponentHeightAboveTheSeaEditValidator = new betterDoubleValidator(
      0, max_refractive_index, max_decimals, ExponentHeightAboveTheSeaEdit);
  ExponentHeightAboveTheSeaEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));

  ExponentHeightAboveTheSeaEdit->setValidator(
      ExponentHeightAboveTheSeaEditValidator);
  exponential_model_layout->addWidget(ExponentHeightAboveTheSeaEdit, 0, 1);

  exponential_model_layout->addWidget(new QLabel(
      "Показатель преломления у поверхности:", section_exponential_model));
  ExponentRefractiveIndexNearSurfaceEdit = new QLineEdit(this);

  auto* ExponentRefractiveIndexNearSurfaceEditValidator =
      new betterDoubleValidator(0, max_refractive_index, max_decimals,
                                ExponentRefractiveIndexNearSurfaceEdit);
  ExponentRefractiveIndexNearSurfaceEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));

  ExponentRefractiveIndexNearSurfaceEdit->setValidator(
      ExponentRefractiveIndexNearSurfaceEditValidator);
  exponential_model_layout->addWidget(ExponentRefractiveIndexNearSurfaceEdit, 1,
                                      1);
  section_exponential_model->setContentLayout(*exponential_model_layout);
  ui->atmosphericStackedWidget->insertWidget(1, section_exponential_model);
  ui->atmosphericStackedWidget->setCurrentIndex(0);

  ui::Section* section_averagek_model =
      new ui::Section("Параметры", 300, this, false, ModelType::Atmospheric);
  auto* averagek_model_layout = new QGridLayout();
  averagekIntegrateButton = new QRadioButton("Численное интегрирование");
  averagekFittingButton = new QRadioButton("Подбор");
  averagek_model_layout->addWidget(averagekIntegrateButton);
  averagek_model_layout->addWidget(averagekFittingButton);
  section_averagek_model->setContentLayout(*averagek_model_layout);
  ui->refractionStackedWidget->insertWidget(2, section_averagek_model);

  ui::Section* section_averagep_model =
      new ui::Section("Параметры", 300, this, false, ModelType::Atmospheric);
  auto* averagep_model_layout = new QGridLayout();
  averagepIntegrateButton = new QRadioButton("Численное интегрирование");
  averagepFittingButton = new QRadioButton("Подбор");
  averagep_model_layout->addWidget(averagepIntegrateButton);
  averagep_model_layout->addWidget(averagepFittingButton);
  section_averagep_model->setContentLayout(*averagep_model_layout);
  ui->refractionStackedWidget->insertWidget(3, section_averagep_model);

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

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_atmosphericModelBox_currentIndexChanged(
    const QString& atmospheric_model) {
  gui::AtmosphericModel current_atmoshperic_model =
      string_to_atmospheric_model[atmospheric_model.toStdString()];
  user_input_data.setAtmosphericModel(current_atmoshperic_model);
  switch (current_atmoshperic_model) {
    case gui::AtmosphericModel::Segmented: {
      ui->atmosphericStackedWidget->setCurrentIndex(0);
      break;
    }
    case gui::AtmosphericModel::Exponential: {
      ui->atmosphericStackedWidget->setCurrentIndex(1);
      break;
    }
    case gui::AtmosphericModel::GOST440481: {
      ui->atmosphericStackedWidget->setCurrentIndex(2);
      break;
    }
  }
  calculateResult();
  showAnswer();
}

void MainWindow::on_refractionModelBox_currentIndexChanged(
    const QString& refraction_model) {
  gui::RefractionModel current_refraction_model =
      string_to_refraction_model[refraction_model.toStdString()];
  user_input_data.setRefractionModel(current_refraction_model);
  switch (current_refraction_model) {
    case gui::RefractionModel::Effective_Radius43: {
      ui->refractionStackedWidget->setCurrentIndex(0);
      break;
    }
    case gui::RefractionModel::Geometric: {
      ui->refractionStackedWidget->setCurrentIndex(1);
      break;
    }
    case gui::RefractionModel::AverageK: {
      ui->refractionStackedWidget->setCurrentIndex(2);
      break;
    }
    case gui::RefractionModel::AverageRho: {
      ui->refractionStackedWidget->setCurrentIndex(3);
      break;
    }
  }
  calculateResult();
  showAnswer();
}

void MainWindow::showAnswer() {
  ui->declinationAngleEdit->setText(QString::number(answer.psi_d));
  ui->slidingAngleEdit->setText(QString::number(answer.psi_g));
  ui->distanceToSurfaceEdit->setText(QString::number(answer.d));
}
