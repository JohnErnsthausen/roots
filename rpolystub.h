#include "rpoly.h"
#include <stdexcept>

#ifndef RPolyStub_h
#define RPolyStub_h

class RPolyStub: public RPoly {
  public:
    int maxDegree;
    int mdp1;
    RPolyStub(int degree);
    ~RPolyStub(void);

    void initialize() override;
    void rpoly(double* op, int Degree, double* zeror, double* zeroi) override;
};

RPolyStub::RPolyStub(int degree): RPoly(degree) {
  maxDegree = degree;
  mdp1 = degree+1;
}

RPolyStub::~RPolyStub(void) {}

void RPolyStub::initialize() {}

void RPolyStub::rpoly(double* op, int Degree, double* zeror, double* zeroi) {
  if (Degree > maxDegree){
    throw std::invalid_argument( "Requested maximal degree is greater than MAXDEGREE." );
  }

 if (op[0]==0.0) {
    throw std::invalid_argument( "The leading coefficient is zero." );
  }

  if (Degree == 9) {
    zeror[0] = 0.065297428539351;
    zeror[1] =-1.0;
    zeror[2] =-2.0;
    zeror[3] =-3.0;
    zeror[4] =-4.0;
    zeror[5] =-0.07;
    zeror[6] = 1.0;
    zeror[7] = 2.0;
    zeror[8] = 3.0;
    zeror[9] = 4.0;
    zeroi[0] = 0.0;
    zeroi[1] = 0.0;
    zeroi[2] = 0.0;
    zeroi[3] =-2.0;
    zeroi[4] =-2.0;
    zeroi[5] = 0.0;
    zeroi[6] = 0.0;
    zeroi[7] = 0.0;
    zeroi[8] = 2.0;
    zeroi[9] = 2.0;
  }
}

#endif

