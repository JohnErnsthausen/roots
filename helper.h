#include <limits>

#ifndef Helper_h
#define Helper_h

class Helper {
  public:
    bool nearly_equal(double a, double b) const;
    bool nearly_equal(double a, double b, int factor) const;
    double absmin(int dim, double x[]) const;
};

bool Helper::nearly_equal(double a, double b) const {
  return std::nextafter(a, std::numeric_limits<double>::lowest()) <= b
      && std::nextafter(a, std::numeric_limits<double>::max()) >= b;
}

bool Helper::nearly_equal(double a, double b, int factor /* a factor of epsilon */) const {
  double min_a = a - (a - std::nextafter(a, std::numeric_limits<double>::lowest())) * factor;
  double max_a = a + (std::nextafter(a, std::numeric_limits<double>::max()) - a) * factor;

  return min_a <= b && max_a >= b;
}

double Helper::absmin(int dim, double* x) const {
  double minimum,tmp;

  minimum = x[0];
  for(int j=1;j<dim;j++) {
    tmp = x[j];
    if(tmp < 0.0) tmp = -tmp;
    minimum = std::min(minimum,tmp);
  }
  return minimum;
}

#endif

