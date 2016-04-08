#include "gtest/gtest.h"

// START:RPolyStub
class RPolyStub {
  public:
    RPolyStub(int degree);
};

RPolyStub::RPolyStub(int degree) {
};
// END:RPolyStub

TEST(RpolyInterface, ConstructorPopulatesMaximalDegree) {
  RPolyStub stub(10);
}

