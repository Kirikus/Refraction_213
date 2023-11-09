#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H

#include "functionmodel1d.h"

class SplineModel : public FunctionModel1D
{
public:
    SplineModel();
    double y(double x) override;
    void fromCSV() override;
private:
    struct IntervalData{
        pair<double, double> start_point;
        pair<double, double> finish_point;
        double a;
        double b;
        bool calculated{false};
        //IntervalData(double x1, double x2, double k1, double b1): start_x{x1}, finish_x{x2}, k{k1}, b{b1}, calculated{true}
        //{};
    };
    vector<struct IntervalData> interval_data;
  };
#endif // SPLINEMODEL_H
