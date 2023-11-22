#include "splinemodel.h"
//#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <algorithm>

SplineModel::SplineModel(vector<Point> points) {
  vector<vector<double>> matrix;
  int eq_number = (points.size() - 1) * 4;
  vector<double> coeff(eq_number, 0);
  vector<double> answer(eq_number, 0);
  for (int i = 0; i < points.size() - 1; ++i) {
    double x1 = points[i].x;
    double x2 = points[i + 1].x;
    double y1 = points[i].y;
    double y2 = points[i + 1].y;
    coeff[4 * i] = 1;
    coeff.push_back(y1);
    matrix.push_back(coeff);
    coeff.assign(eq_number, 0);
    coeff[4 * i] = 1;
    coeff[4 * i + 1] = (x2 - x1);
    coeff[4 * i + 2] = (x2 - x1) * (x2 - x1);
    coeff[4 * i + 3] = (x2 - x1) * (x2 - x1) * (x2 - x1);
    coeff.push_back(y2);
    matrix.push_back(coeff);
    coeff.assign(eq_number, 0);
    if (i < points.size() - 2) {
      coeff[4 * i + 1] = 1;
      coeff[4 * i + 2] = 2 * (x2 - x1);
      coeff[4 * i + 3] = 3 * (x2 - x1) * (x2 - x1);
      coeff[4 * i + 5] = -1;
      coeff.push_back(0);
      matrix.push_back(coeff);
      coeff.assign(eq_number, 0);
      coeff[4 * i + 2] = 2;
      coeff[4 * i + 3] = 6 * (x2 - x1);
      coeff[4 * (i + 1) + 2] = -2;
      coeff.push_back(0);
      matrix.push_back(coeff);
      coeff.assign(eq_number, 0);
    }
    if (i == 0) {
      coeff[4 * i + 2] = 2;
      coeff.push_back(0);
      matrix.push_back(coeff);
      coeff.assign(eq_number, 0);
    }
  }
  coeff[4 * (points.size() - 2) + 2] = 2;
  coeff[4 * (points.size() - 2) + 3] =
      6 * (points.back().x - points[points.size() - 2].x);
  coeff.push_back(0);
  matrix.push_back(coeff);
  coeff.assign(eq_number, 0);
  for (int i = 0; i < eq_number; ++i) {
    if (matrix[i][i] == 0) {
      int search = i;
      while (matrix[search][i] == 0 && search < eq_number) search += 1;
      if (search == eq_number - 1) continue;
      for (int l = 0; l < matrix[search].size(); ++l) {
        double tmp = matrix[search][l];
        matrix[search][l] = matrix[i][l];
        matrix[i][l] = tmp;
      }
    }
    double tmp = matrix[i][i];
    for (int j = eq_number; j >= i; --j) matrix[i][j] /= tmp;
    for (int g = i + 1; g < eq_number; g++) {
      tmp = matrix[g][i];
      for (int k = eq_number; k >= i; --k) matrix[g][k] -= tmp * matrix[i][k];
    }
  }
  answer[eq_number - 1] = matrix[eq_number - 1][eq_number];
  for (int i = eq_number - 2; i >= 0; i--) {
    answer[i] = matrix[i][eq_number];
    for (int j = i + 1; j < eq_number; j++)
      answer[i] -= matrix[i][j] * answer[j];
    // TODO: Think about c0 coefficient from YouTube example
  }
  for (int i = 0; i < points.size() - 1; ++i) {
    data.push_back(Data(points[i], points[i + 1], answer[4 * i],
                        answer[4 * i + 1], answer[4 * i + 2],
                        answer[4 * i + 3]));
  }
}

SplineModel::SplineModel(QFile& file) {
  vector<Point> data;
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << "File not exists";
  } else {
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      vector<double> coords;
      for (QString item : line.split(";")) coords.push_back(item.toDouble());
      data.push_back(Point(coords));
    }
  }
  SplineModel* spline = new SplineModel(data);
  this->data = spline->data;
  file.close();
}

double SplineModel::y(double x) {
  auto start = data.begin();
  auto finish = data.end();
  finish--;
  if (x <= start->first_point.x)
    return data[0].a + data[0].b * (x - data[0].first_point.x);
  if (x >= finish->second_point.x)
    return data.back().a + data.back().b * (x - data.back().first_point.x);
  for (auto interval = data.begin(); interval != data.end(); ++interval)
    if (x >= interval->first_point.x && x <= interval->second_point.x) {
      double x0 = interval->first_point.x;
      return interval->a + interval->b * (x - x0) +
             interval->c * (x - x0) * (x - x0) +
             interval->d * (x - x0) * (x - x0) * (x - x0);
    }
}
