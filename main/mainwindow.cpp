#include "mainwindow.h"

#include <QLocale>
#include <QString>
#include <iostream>

#include "./ui_mainwindow.h"
#include "Section.h"
#include "calculateResult.h"
#include "doubleValidator.h"
#include "plotting.h"

constexpr double min_height = -500;
constexpr double max_distance = 1000000;
constexpr double max_height = 15000;
constexpr double max_decimals = 5;
constexpr double max_surface_height = 20000;
constexpr double max_refractive_index = 2000;

std::map<std::string, gui::AtmosphericModel> string_to_atmospheric_model = {
    {"Модель ГОСТ4401-81", gui::AtmosphericModel::GOST440481},
    {"Сегментированная модель", gui::AtmosphericModel::Segmented},
    {"Экспоненциальная модель", gui::AtmosphericModel::Exponential}};
std::map<std::string, gui::RefractionModel> string_to_refraction_model = {
    {"Модель плоской Земли", gui::RefractionModel::GeometricLine},
    {"Модель эффективного радиуса 4/3",
     gui::RefractionModel::Effective_Radius43},
    {"Геометрическая модель", gui::RefractionModel::Geometric},
    {"Модель среднего K", gui::RefractionModel::AverageK},
    {"Модель среднего P", gui::RefractionModel::AverageRho}};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto* stationCoordinatesValidator = new betterDoubleValidator(
      min_height, max_height, max_decimals,
      ui->stationCoordinatesEdit);  // Создаем валидатор, позволяющий вводить
                                    // только числа с плавающий точкой в поле
                                    // высоты станции
  stationCoordinatesValidator->setLocale(QLocale(
      QLocale::English,
      QLocale::Europe));  // Ставим локаль, где разделительный символ - '.'
  ui->stationCoordinatesEdit->setValidator(
      stationCoordinatesValidator);  // Ставим валидатор для поля ввода
                                     // высоты станции

  auto* targetCoordinatesValidator = new betterDoubleValidator(
      min_height, max_height, max_decimals,
      ui->stationCoordinatesEdit);  // Создаем валидатор, позволяющий вводить
                                    // только числа с плавающий точкой в поле
                                    // высоты цели
  targetCoordinatesValidator->setLocale(QLocale(
      QLocale::English,
      QLocale::Europe));  // Ставим локаль, где разделительный символ - '.'
  ui->targetCoordinatesEdit->setValidator(
      targetCoordinatesValidator);  // Ставим валидатор для поля ввода
                                    // высоты цели

  auto* distanceCoordinatesValidator = new betterDoubleValidator(
      0, max_distance, max_decimals,
      ui->distanceToTargetEdit);  // Создаем валидатор, позволяющий вводить
                                  // только числа с плавающий точкой в поле
                                  // расстояния между станцией и целью
  distanceCoordinatesValidator->setLocale(QLocale(
      QLocale::English,
      QLocale::Europe));  // Ставим локаль, где разделительный символ - '.'
  ui->distanceToTargetEdit->setValidator(
      distanceCoordinatesValidator);  // Ставим валидатор для поля ввода
                                      // расстояния между станцией и целью

  ui->plot->xAxis->setRange(0, 10000);  // Масштаб по оси Х
  ui->plot->yAxis->setRange(0, 10000);  // Масштаб по оси Y
  ui->plot->xAxis->setLabel(
      "Расстояние по земной поверхности, м");  // Подпись оси Х
  ui->plot->yAxis->setLabel("Высота, м");      // Подпись оси Y

  ui->plot->setInteraction(
      QCP::iRangeZoom, true);  // Включаем взаимодействие удаления/приближения
  ui->plot->setInteraction(
      QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика

  user_input_data.setPlot(ui->plot);

  // Создаем и добавляем секцию для задания сегментированной модели атмосферы
  // label и LineEdit для высоты поверхности:

  ui::Section* section_segmented_model = new ui::Section(
      "Параметры", 300, this, false,
      ModelType::Atmospheric);  // Создаем Секцию с подписью "Параметры"
  auto* segmented_model_layout =
      new QGridLayout();  // Создаем layout для этой секции
  segmented_model_layout->addWidget(
      new QLabel("Высота поверхности над уровнем моря:",
                 section_segmented_model));  // Добавляем label в layout

  SegmentedHeightAboveTheSeaEdit = new QLineEdit(
      this);  // Создаем LineEdit, куда будем записывать высоту поверхности

  auto* SegmentedHeightAboveTheSeaEditValidator = new betterDoubleValidator(
      0, max_surface_height, max_decimals, SegmentedHeightAboveTheSeaEdit);
  SegmentedHeightAboveTheSeaEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));
  SegmentedHeightAboveTheSeaEdit->setValidator(
      SegmentedHeightAboveTheSeaEditValidator);  // Ставим этому LineEdit'y
                                                 // валидатор

  segmented_model_layout->addWidget(SegmentedHeightAboveTheSeaEdit, 0,
                                    1);  // Добавляем этот LineEdit на layout

  // label и LineEdit для индекса рефракции:

  segmented_model_layout->addWidget(
      new QLabel("Показатель преломления у поверхности:",
                 section_segmented_model));  // Добавляем label в layout
  SegmentedRefractiveIndexNearSurfaceEdit = new QLineEdit(
      this);  // Создаем LineEdit, куда будем записывать индекс рефракции

  auto* SegmentedRefractiveIndexNearSurfaceEditValidator =
      new betterDoubleValidator(0, max_refractive_index, max_decimals,
                                SegmentedRefractiveIndexNearSurfaceEdit);
  SegmentedRefractiveIndexNearSurfaceEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));

  SegmentedRefractiveIndexNearSurfaceEdit->setValidator(
      SegmentedRefractiveIndexNearSurfaceEditValidator);  // Ставим Валидатор
                                                          // этому LineEdit'y
  segmented_model_layout->addWidget(SegmentedRefractiveIndexNearSurfaceEdit, 1,
                                    1);  // Добавляем этот LineEdit на layout
  section_segmented_model->setContentLayout(*segmented_model_layout);
  ui->atmosphericStackedWidget->insertWidget(
      0, section_segmented_model);  // Ставим на 0 позицию в StackedWidget'e для
                                    // Атмосферы

  // Создаем и добавляем секцию для задания экспоненциальной модели атмосферы
  // label и LineEdit для высоты поверхности:

  ui::Section* section_exponential_model = new ui::Section(
      "Параметры", 300, this, false,
      ModelType::Atmospheric);  // Создаем Секцию с подписью "Параметры"
  auto* exponential_model_layout =
      new QGridLayout();  // Создаем layout для этой секции
  exponential_model_layout->addWidget(
      new QLabel("Высота поверхности над уровнем моря:",
                 section_exponential_model));  // Добавляем label в layout

  ExponentHeightAboveTheSeaEdit = new QLineEdit(
      this);  // Создаем LineEdit, куда будем записывать высоту поверхности

  auto* ExponentHeightAboveTheSeaEditValidator = new betterDoubleValidator(
      0, max_refractive_index, max_decimals, ExponentHeightAboveTheSeaEdit);
  ExponentHeightAboveTheSeaEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));

  ExponentHeightAboveTheSeaEdit->setValidator(
      ExponentHeightAboveTheSeaEditValidator);  // Ставим валидатор этому
                                                // LineEdit'y
  exponential_model_layout->addWidget(ExponentHeightAboveTheSeaEdit, 0,
                                      1);  // Добавляем этот LineEdit на layout

  // label и LineEdit для индекса рефракции:

  exponential_model_layout->addWidget(
      new QLabel("Показатель преломления у поверхности:",
                 section_exponential_model));  // Добавляем label в layout
  ExponentRefractiveIndexNearSurfaceEdit = new QLineEdit(
      this);  // Создаем LineEdit, куда будем записывать индекс рефракции

  auto* ExponentRefractiveIndexNearSurfaceEditValidator =
      new betterDoubleValidator(0, max_refractive_index, max_decimals,
                                ExponentRefractiveIndexNearSurfaceEdit);
  ExponentRefractiveIndexNearSurfaceEditValidator->setLocale(
      QLocale(QLocale::English, QLocale::Europe));

  ExponentRefractiveIndexNearSurfaceEdit->setValidator(
      ExponentRefractiveIndexNearSurfaceEditValidator);  // Ставим валидатор
                                                         // этому LineEdit'y
  exponential_model_layout->addWidget(ExponentRefractiveIndexNearSurfaceEdit, 1,
                                      1);  // Добавляем этот LineEdit на layout
  section_exponential_model->setContentLayout(
      *exponential_model_layout);  // Привязываем layout к Секции
  ui->atmosphericStackedWidget->insertWidget(
      1, section_exponential_model);  // Ставим на 1 позицию в StackedWidget'e
                                      // для Атмосферы

  ui->atmosphericStackedWidget->setCurrentIndex(
      0);  // Выставляем Сегментированную модель по умолчанию

  // Создаем и добавляем секцию для задания модели атмосферы ГОСТ 4401-81
  // Создаем кнопку загрузки данных из файла
  auto* gost_tab_widget = new QTabWidget();

  ui::Section* section_gost_model_temperature = new ui::Section(
      "Параметры Температуры", 300, this, false, ModelType::Atmospheric);
  auto* gost_model_layout_temperature = new QGridLayout();
  downloadTemperatureGostButton = new QPushButton(
      "Загрузить Температуру из файла", section_gost_model_temperature);
  gost_model_layout_temperature->addWidget(downloadTemperatureGostButton);
  temperatureLinearButton =
      new QRadioButton("Использовать линейную интерполяцию");
  gost_model_layout_temperature->addWidget(temperatureLinearButton);
  temperatureSplineButton =
      new QRadioButton("Использовать Spline интерполяцию");
  gost_model_layout_temperature->addWidget(temperatureSplineButton);
  section_gost_model_temperature->setContentLayout(
      *gost_model_layout_temperature);
  gost_tab_widget->addTab(section_gost_model_temperature, "Температура");

  ui::Section* section_gost_model_pressure = new ui::Section(
      "Параметры Давления", 300, this, false, ModelType::Atmospheric);
  auto* gost_model_layout_pressure = new QGridLayout();
  downloadPressureGostButton = new QPushButton("Загрузить Давление из файла",
                                               section_gost_model_pressure);
  gost_model_layout_pressure->addWidget(downloadPressureGostButton);
  pressureLinearButton = new QRadioButton("Использовать линейную интерполяцию");
  gost_model_layout_pressure->addWidget(pressureLinearButton);
  pressureSplineButton = new QRadioButton("Использовать Spline интерполяцию");
  gost_model_layout_pressure->addWidget(pressureSplineButton);
  section_gost_model_pressure->setContentLayout(*gost_model_layout_pressure);

  gost_tab_widget->addTab(section_gost_model_pressure, "Давление");

  ui->atmosphericStackedWidget->insertWidget(2, gost_tab_widget);

  // Создаем и добавляем секцию для задания модели рефракции Среднее К

  ui::Section* section_averagek_model =
      new ui::Section("Параметры", 300, this, false, ModelType::Atmospheric);
  auto* averagek_model_layout =
      new QGridLayout();  // Создаем layout для этой секции
  averagekIntegrateButton = new QRadioButton(
      "Численное интегрирование");  // Создаем кнопку, позволяющую выбрать
                                    // способ подсчета Численное Интегрирование
  averagekFittingButton = new QRadioButton(
      "Подбор");  // Создаем кнопку, позволяющую выбрать способ подсчета Подбор
  averagek_model_layout->addWidget(averagekIntegrateButton);
  averagek_model_layout->addWidget(
      averagekFittingButton);  // Добавляем кнопки на layout
  section_averagek_model->setContentLayout(
      *averagek_model_layout);  // Привязываем layout к Секции
  ui->refractionStackedWidget->insertWidget(
      2, section_averagek_model);  // Ставим на 2 позицию в StackedWidget'e для
                                   // Рефракции

  ui::Section* section_averagep_model = new ui::Section(
      "Параметры", 300, this, false,
      ModelType::Atmospheric);  // Создаем Секцию с подписью "Параметры"
  auto* averagep_model_layout = new QGridLayout();
  averagepIntegrateButton = new QRadioButton(
      "Численное интегрирование");  // Создаем кнопку, позволяющую выбрать
                                    // способ подсчета Численное Интегрирование
  averagepFittingButton = new QRadioButton(
      "Подбор");  // Создаем кнопку, позволяющую выбрать способ подсчета Подбор
  averagep_model_layout->addWidget(averagepIntegrateButton);
  averagep_model_layout->addWidget(
      averagepFittingButton);  // Добавляем кнопки на layout
  section_averagep_model->setContentLayout(
      *averagep_model_layout);  // Привязываем layout к Секции
  ui->refractionStackedWidget->insertWidget(
      3, section_averagep_model);  // Ставим на 2 позицию в StackedWidget'e для
                                   // Рефракции

  // Привязываем функции, которые будут вызываться при изменении параметров
  // моделей атмосферы и рефракции

  QObject::connect(
      ExponentRefractiveIndexNearSurfaceEdit, &QLineEdit::textEdited, this,
      &MainWindow::ExponentRefractiveIndexNearSurfaceEdit_textEdited);

  QObject::connect(ExponentHeightAboveTheSeaEdit, &QLineEdit::textEdited, this,
                   &MainWindow::ExponentHeightAboveTheSeaEdit_textEdited);

  QObject::connect(SegmentedHeightAboveTheSeaEdit, &QLineEdit::textEdited, this,
                   &MainWindow::SegmentedHeightAboveTheSeaEdit_textEdited);

  QObject::connect(
      SegmentedRefractiveIndexNearSurfaceEdit, &QLineEdit::textEdited, this,
      &MainWindow::SegmentedRefractiveIndexNearSurfaceEdit_textEdited);

  QObject::connect(averagekIntegrateButton, &QRadioButton::clicked, this,
                   &MainWindow::on_integrateButton_clicked);
  QObject::connect(averagepIntegrateButton, &QRadioButton::clicked, this,
                   &MainWindow::on_integrateButton_clicked);
  QObject::connect(averagekFittingButton, &QRadioButton::clicked, this,
                   &MainWindow::on_fittingButton_clicked);
  QObject::connect(averagepFittingButton, &QRadioButton::clicked, this,
                   &MainWindow::on_fittingButton_clicked);

  QObject::connect(downloadTemperatureGostButton, &QPushButton::clicked, this,
                   &MainWindow::on_downloadTemperatureGostButton_clicked);
  QObject::connect(temperatureSplineButton, &QRadioButton::clicked, this,
                   &MainWindow::on_temperatureSplineButton_clicked);
  QObject::connect(temperatureLinearButton, &QRadioButton::clicked, this,
                   &MainWindow::on_temperatureLinearButton_clicked);

  QObject::connect(downloadPressureGostButton, &QPushButton::clicked, this,
                   &MainWindow::on_downloadPressureGostButton_clicked);
  QObject::connect(pressureSplineButton, &QRadioButton::clicked, this,
                   &MainWindow::on_pressureSplineButton_clicked);
  QObject::connect(pressureLinearButton, &QRadioButton::clicked, this,
                   &MainWindow::on_pressureLinearButton_clicked);
}

void MainWindow::showAnswer() {
  ui->declinationAngleEdit->setText(QString::number(answer.psi_d));
  ui->slidingAngleEdit->setText(QString::number(answer.psi_g));
  ui->distanceToSurfaceEdit->setText(QString::number(answer.d));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_downloadTemperatureGostButton_clicked() {
  QFile gost_qfile(QFileDialog::getOpenFileName(0, "Открыть модель ГОСТ4401-81",
                                                "", "*.csv"));
  if (!gost_qfile.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox* msg = new QMessageBox(this);
    msg->setWindowTitle("Ошибка чтения файла");
    msg->setText("Не удалось прочитать информацию о модели");
    msg->show();
    return;
  }
  std::vector<std::string> gost_temperature_data;
  QTextStream in(&gost_qfile);
  while (!in.atEnd())
    gost_temperature_data.push_back(in.readLine().toStdString());
  user_input_data.setGostTemperature(gost_temperature_data);
  calculateAndShow();
}

void MainWindow::on_downloadPressureGostButton_clicked() {
  QFile gost_qfile(QFileDialog::getOpenFileName(0, "Открыть модель ГОСТ4401-81",
                                                "", "*.csv"));
  if (!gost_qfile.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox* msg = new QMessageBox(this);
    msg->setWindowTitle("Ошибка чтения файла");
    msg->setText("Не удалось прочитать информацию о модели");
    msg->show();
    return;
  }
  std::vector<std::string> gost_pressure_data;
  QTextStream in(&gost_qfile);
  while (!in.atEnd()) gost_pressure_data.push_back(in.readLine().toStdString());
  user_input_data.setGostPressure(gost_pressure_data);
  calculateAndShow();
}

void MainWindow::calculateAndShow() {
  calculateResult();
  user_input_data.setAnswer(answer);
  addTargetAndStation();
  showAnswer();
}

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
  calculateAndShow();
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
    case gui::RefractionModel::GeometricLine: {
      ui->refractionStackedWidget->setCurrentIndex(0);
      break;
    }
  }
  calculateAndShow();
}

void MainWindow::on_temperatureSplineButton_clicked() {
  user_input_data.setTemperatureInterpolationMethod(gui::Spline);
  calculateAndShow();
}

void MainWindow::on_temperatureLinearButton_clicked() {
  user_input_data.setTemperatureInterpolationMethod(gui::Linear);
  calculateAndShow();
}

void MainWindow::on_pressureSplineButton_clicked() {
  user_input_data.setPressureInterpolationMethod(gui::Spline);
  calculateAndShow();
}

void MainWindow::on_pressureLinearButton_clicked() {
  user_input_data.setPressureInterpolationMethod(gui::Linear);
  calculateAndShow();
}
