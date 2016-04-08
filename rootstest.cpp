#include "gmock/gmock.h"

class Roots {
};

TEST(RootFinder, GetMaximalDegree) {
  Roots rootfinder();
  ASSERT_THAT(rootfinder.getMaxDegree(), Eq(10));
}

