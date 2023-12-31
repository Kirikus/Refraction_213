#include "splinemodel.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
SplineModel::SplineModel(std::vector<Point> points) {
  std::vector<std::vector<double>> matrix;
  int eq_number = (points.size() - 1) * 4;
  std::vector<double> coeff(eq_number, 0);
  std::vector<double> answer(eq_number, 0);
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
    data.push_back(Data(points[i].x, points[i + 1].x, answer[4 * i],
                        answer[4 * i + 1], answer[4 * i + 2],
                        answer[4 * i + 3]));
  }
}
SplineModel::SplineModel(std::vector<std::string>& file_data) {
  std::vector<Point> data;
  for (int i = 0; i < file_data.size(); ++i) {
    std::vector<double> coords;
    std::string line = file_data[i];
    std::string delimiter = ";";
    size_t pos = 0;
    std::string token;
    std::vector<std::string> parts;
    while ((pos = line.find(delimiter)) != std::string::npos) {
      token = line.substr(0, pos);
      parts.push_back(token);
      line.erase(0, pos + delimiter.length());
    }
    parts.push_back(line);
    if (parts.size() != 2) throw std::runtime_error("Wrong format of string");
    for (int i = 0; i < 2; ++i) {
      try {
        double d = std::stod(parts[i]);
      } catch (const std::invalid_argument&) {
        throw std::runtime_error("Wrong format of string");
      }
      coords.push_back(std::stod(parts[i]));
    }
    data.push_back(Point(coords[0], coords[1]));
  }
  SplineModel* spline = new SplineModel(data);
  this->data = spline->data;
}

double SplineModel::y(double x) {
  if (data.size() == 0) return 0;
  auto start = data.begin();
  auto finish = data.end();
  finish--;
  if (x < start->first_x) return (start->b) * (x - start->first_x) + start->a;
  if (x > data.back().second_x) {
    double final_value =
        data.back().d *
            std::pow(data.back().second_x - data.back().first_x, 3) +
        data.back().c *
            std::pow(data.back().second_x - data.back().first_x, 2) +
        data.back().b * (data.back().second_x - data.back().first_x) +
        data.back().a;
    return (3 * data.back().d *
                std::pow(data.back().second_x - data.back().first_x, 2) +
            2 * data.back().c * (data.back().second_x - data.back().first_x) +
            data.back().b) *
               (x - data.back().second_x) +
           final_value;
  }
  for (auto interval = data.begin(); interval != data.end(); ++interval)
    if (x >= interval->first_x && x <= interval->second_x) {
      double x0 = interval->first_x;
      return interval->a + interval->b * (x - x0) +
             interval->c * (x - x0) * (x - x0) +
             interval->d * (x - x0) * (x - x0) * (x - x0);
    }
}
