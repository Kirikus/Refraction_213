#include "splinemodel.h"

SplineModel::SplineModel()
{
}
double SplineModel::y(double x){
    auto start = data.begin();
    auto finish = data.end();
    finish--;
    if (x <= (start->x)) return start->y;
    if (x >= (finish->x)) return finish->y;
    for (int i = 0; i < interval_data.size(); ++i){
        auto interval = interval_data[i];
        if (x >= interval.start_x && x <= interval.finish_x) return interval.k * x + interval.b;
    }
    auto it_higher = upper_bound(data.begin(), data.end(), make_pair(x, -1));
    auto it_lower = it_higher--;
    double x0 = (it_lower)->x;
    double x1 = (it_higher)->x;
    double y0 = (it_lower)->y;
    double y1 = (it_higher)->y;
       double x0 = -1;
       double y0 = 0.5;
       double x1 = 0;
       double y1 = 0;
       double x2 = 3;
       double y2 = 3;
        double a11 = 2 / (x1 - x0);
            double a12 = 1 / (x1 - x0);
            double a21 = 1 / (x1 - x0);
            double a22 = 2 * ((1 / (x1 - x0) + 1 / (x2 - x1)));
            double a23 = 1 / (x2 - x1);
            double a32 = 1 / (x2 - x1);
            double a33 = 2 / (x2 - x1);
            double b1 = (3 * (y1 - y0)) / ((x1 - x0) * (x1 - x0));
            double b2 = 3 * (((y1 - y0) / ((x1 - x0) * (x1 - x0))) + ((y2 - y1) / ((x2 - x1) * (x2 - x1))));
            double b3 = 3 * (y2 - y1) / ((x2 - x1) * (x2 - x1));
            double A = a21 * b1 / a11;
            double B = a12 * a21 / a11;
            double C = a22;
            double D = b3 * a23 / a33;
            double E = a23 * a32 / a33;
            double F = b2;
            double k1 = (A + D - F) / (B + E - C);
            double k0 = (b1 - a12 * k1) / a11;
            double k2 = (b3 - a32 * k1) / a33;
            double a1 = k0 * (x1 - x0) - (y1 - y0);
            double c1 = -k1 * (x1 - x0) + (y1 - y0);
            double a2 = k1 * (x2 - x1) - (y2 - y1);
            double c2 = -k2 * (x2 - x1) + (y2 - y1);
            double t = (x - x1) / (x2 - x1);
            double q1 = (1 - t) * y0 + t * y1 + t * (1 - t)*((1 - t) * a1 + t * b1);
    }

}
