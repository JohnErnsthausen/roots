#include "gmock/gmock.h"

using namespace testing;

// START:RPolyStub
class RPolyStub {
  public:
    int maxDegree;
    int mdp1;
    RPolyStub(int degree);
};

RPolyStub::RPolyStub(int degree) {
  maxDegree = degree;
  mdp1 = degree+1;
}
// END:RPolyStub

TEST(RpolyInterface, ConstructorPopulatesMaximalDegree) {
  RPolyStub stub(10);
  ASSERT_THAT(stub.maxDegree, Eq(10));
}

TEST(RpolyInterface, ConstructorPopulatesMaximalDegreePlusOne) {
  RPolyStub stub(10);
  ASSERT_THAT(stub.mdp1, Eq(11));
}

