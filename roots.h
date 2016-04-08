#include "rpoly.h"
#include "helper.h"

#include <vector>

#ifndef Roots_h
#define Roots_h

class Roots {
  int maxDegree;
  int mdp1;
  int degree;
  int realRoots;

  public:
    Roots(RPoly* rpoly);
    ~Roots(void);
    int getMaxDegree(void) const;
    void findRoots(const std::vector<double>& coeff);
    void findRealRoots(void);
    void getRoots(int& Degree, std::vector<double>& zr, std::vector<double>& zi) const;
    double getAbsMinRealRoot(void) const;

  private:
    RPoly* rpoly_;
    Helper helper;

    double* zeror{nullptr};
    double* zeroi{nullptr};
    double* op{nullptr};
};

Roots::Roots(RPoly* rpoly) : rpoly_(rpoly) {
  maxDegree = rpoly_->maxDegree;
  mdp1  = rpoly_->mdp1;
  zeror = new double[maxDegree];
  zeroi = new double[maxDegree];
  op    = new double[mdp1];
}

Roots::~Roots(void) {
  delete [] zeror;
  delete [] zeroi;
  delete [] op;
  zeror = nullptr;
  zeroi = nullptr;
  op    = nullptr;
  rpoly_= nullptr;
}

int Roots::getMaxDegree(void) const {
  return maxDegree;
}

void Roots::findRoots(const std::vector<double>& coeff) {
  degree = coeff.size()-1;
  for(int j=0; j<=degree; j++) {
    op[j] = coeff[j];
  }

  rpoly_->initialize();
  // Know length(coeff) .leq. length(op) because degree .leq. rpoly_->maxDegree
  rpoly_->rpoly(op, degree, zeror, zeroi);

  findRealRoots();
}

void Roots::findRealRoots(void) {
  realRoots=0;
  for(int j=0;j<degree;j++) {
    if(helper.nearly_equal(zeroi[j], 0.0, 10)) {
      op[realRoots++] = zeror[j];
    }
  }
  return;
}

void Roots::getRoots(int& Degree, std::vector<double>& zr, std::vector<double>& zi) const {
  Degree = degree;
  for(int j=0; j<=degree; j++) {
    zr.push_back(zeror[j]);
    zi.push_back(zeroi[j]);
  }
  return;
}

double Roots::getAbsMinRealRoot(void) const {
  return helper.absmin(realRoots, op);
}

#endif

