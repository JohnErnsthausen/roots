#include "gmock/gmock.h"

#include "rpoly.h"

using namespace testing;

// START:RPolyStub
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

void RPolyStub::rpoly(double* op, int Degree, double* zeror, double* zeroi) {}
// END:RPolyStub

TEST(RpolyInterface, ConstructorPopulatesMaximalDegree) {
  RPolyStub stub(10);
  ASSERT_THAT(stub.maxDegree, Eq(10));
}

TEST(RpolyInterface, ConstructorPopulatesMaximalDegreePlusOne) {
  RPolyStub stub(10);
  ASSERT_THAT(stub.mdp1, Eq(11));
}

TEST(RpolyInterface, HasBaseClassVariableMaxDegree) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(10);

  ASSERT_THAT(rpoly->maxDegree, Eq(10));
  
  delete rpoly;
  rpoly = nullptr;
}

