#include "linearmodel.h"

#include <QDebug>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
using std::ifstream;
using std::stringstream;
LinearModel::LinearModel(vector<Point> points_data) {
  for (auto point = points_data.begin(); point != points_data.end(); point++) {
    auto first_point = point;
    auto second_point = point;
    second_point++;
    if (second_point == points_data.end()) return;
    double x1 = first_point->x;
    double x2 = second_point->x;
    double y1 = first_point->y;
    double y2 = second_point->y;
    double k = (y2 - y1) / (x2 - x1);
    double b = y1 - k * x1;
    data.push_back(Data(x1, x2, k, b));
  }
}

LinearModel::LinearModel(std::string path) {
  vector<Point> data;
  ifstream file;
  file.open(path);
  string file_line;
  while (getline(file, file_line)) {
    vector<double> coords;
    stringstream input_string(file_line);
    string line = input_string.str();
    string delimiter = ";";
    size_t pos = 0;
    string token;
    vector<string> parts;
    while ((pos = line.find(delimiter)) != string::npos) {
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
  LinearModel* interp = new LinearModel(data);
  this->data = interp->data;
  file.close();
}
double LinearModel::y(double x) {
  if (data.size() == 0) return 0;
  auto start = data.begin();
  auto finish = data.end();
  finish--;
  if (x <= (start->first_x)) return start->k * x + start->b;
  if (x >= (finish->second_x)) return finish->k * x + finish->b;
  for (auto interval = data.begin(); interval != data.end(); ++interval)
    if (x >= interval->first_x && x <= interval->second_x)
      return interval->k * x + interval->b;
}
