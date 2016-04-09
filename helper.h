#include <limits>

#ifndef Helper_h
#define Helper_h

class Helper {
  public:
    bool nearly_equal(double a, double b) const;
    bool nearly_equal(double a, double b, int factor) const;
    double absmin(int dim, double* x) const;
    double minpos(int dim, double* x) const;
    double maxpos(int dim, double* x) const;
    double minneg(int dim, double* x) const;
    double maxneg(int dim, double* x) const;
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

// Code duplication should be eliminated!

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

double Helper::minpos(int dim, double* x) const {
  int k{0};
  double minimum,tmp;

  do {
    // std::cout << "k = " << k << std::endl;
    minimum = x[k++];
  } while( minimum < 0.0 && k<dim );
  // std::cout << "k = " << k << std::endl;
  for(int j=k;j<dim;j++) {
    tmp = x[j];
    if(tmp > 0.0 && tmp < minimum) minimum = tmp;
  }
  return minimum;
}

double Helper::maxpos(int dim, double* x) const {
  int k{0};
  double maximum,tmp;

  do {
    // std::cout << "k = " << k << std::endl;
    maximum = x[k++];
  } while( maximum < 0.0 && k<dim );
  // std::cout << "k = " << k << std::endl;
  for(int j=k;j<dim;j++) {
    tmp = x[j];
    if(tmp > 0.0 && tmp > maximum) maximum = tmp;
  }
  return maximum;
}

double Helper::minneg(int dim, double* x) const {
  int k{0};
  double minimum,tmp;

  do {
    // std::cout << "k = " << k << std::endl;
    minimum = x[k++];
  } while( minimum > 0.0 && k<dim );
  // std::cout << "k = " << k << std::endl;
  for(int j=k;j<dim;j++) {
    tmp = x[j];
    if(tmp < 0.0 && tmp > minimum) minimum = tmp;
  }
  return minimum;
}

double Helper::maxneg(int dim, double* x) const {
  int k{0};
  double maximum,tmp;

  do {
    // std::cout << "k = " << k << std::endl;
    maximum = x[k++];
  } while( maximum > 0.0 && k<dim );
  // std::cout << "k = " << k << std::endl;
  for(int j=k;j<dim;j++) {
    tmp = x[j];
    if(tmp < 0.0 && tmp < maximum) maximum = tmp;
  }
  return maximum;
}

#endif

