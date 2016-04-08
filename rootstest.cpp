#include "gmock/gmock.h"

#include "rpoly.h"
#include "rpolystub.h"

using namespace testing;

class Roots {
  int maxDegree;

  public:
    Roots(RPoly* rpoly);
    ~Roots(void);
    int getMaxDegree(void) const;

  private:
    RPoly* rpoly_;
};

Roots::Roots(RPoly* rpoly) : rpoly_(rpoly) {
  maxDegree = rpoly_->maxDegree;
}

Roots::~Roots(void) {
}

int Roots::getMaxDegree(void) const {
  return maxDegree;
}

TEST(RootFinder, GetMaximalDegreeFromStub) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(10);

  Roots rootfinder(rpoly);
  ASSERT_THAT(rootfinder.getMaxDegree(), Eq(10));
  
  delete rpoly;
  rpoly = nullptr;
}

