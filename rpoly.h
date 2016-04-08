#ifndef RPoly_h
#define RPoly_h

class RPoly {
  public:
    int maxDegree;
    int mdp1;
    RPoly(int maxDeg) : maxDegree(maxDeg), mdp1(maxDeg+1) {};
    virtual ~RPoly(void) {};
    virtual void initialize() = 0;
    // rpoly must check degree less than or equal to maxDegree
    // rpoly must check leading coefficient is not zero
    virtual void rpoly(double* op, int degree, double* zeror, double* zeroi) = 0;
};

#endif

