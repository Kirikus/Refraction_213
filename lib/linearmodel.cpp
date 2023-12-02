#include "linearmodel.h"

#include <QDebug>
#include <algorithm>
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

LinearModel::LinearModel(QFile& file) {
  vector<Point> data;
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << "File not exists";
  } else {
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      vector<double> coords;
      for (QString item : line.split(";")) coords.push_back(item.toDouble());
      data.push_back(Point(coords[0], coords[1]));
    }
  }
  LinearModel* line = new LinearModel(data);
  this->data = line->data;
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
