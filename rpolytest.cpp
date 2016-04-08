#include "gtest/gtest.h"
#include "rpoly.h"

TEST(RpolyInterface, ConstructorPopulatesMaximalDegree) {
  RPoly = new RPolyStub(10);
}

