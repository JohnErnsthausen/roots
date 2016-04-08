#include "gmock/gmock.h"

using namespace testing;

// START:RPolyStub
class RPolyStub {
  public:
    int maxDegree;
    RPolyStub(int degree);
};

RPolyStub::RPolyStub(int degree) {
  maxDegree = degree;
}
// END:RPolyStub

TEST(RpolyInterface, ConstructorPopulatesMaximalDegree) {
  RPolyStub stub(10);
  ASSERT_THAT(stub.maxDegree, Eq(10));
}

