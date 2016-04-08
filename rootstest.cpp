#include "gmock/gmock.h"

#include "rpoly.h"
#include "rpolystub.h"

#include <vector>

using namespace testing;

class Roots {
  int maxDegree;
  int mdp1;
  int degree;

  public:
    Roots(RPoly* rpoly);
    ~Roots(void);
    int getMaxDegree(void) const;
    void findRoots(const std::vector<double>& coeff);
    void getRoots(int Degree, std::vector<double>& zr, std::vector<double>& zi) const;

  private:
    RPoly* rpoly_;

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

  return;
}

void Roots::getRoots(int Degree, std::vector<double>& zr, std::vector<double>& zi) const {
  Degree = degree;
  for(int j=0; j<=degree; j++) {
    zr.push_back(zeror[j]);
    zi.push_back(zeroi[j]);
  }
  return;
}

TEST(RootFinder, GetMaximalDegreeFromStub) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(10);

  Roots rootfinder(rpoly);
  ASSERT_THAT(rootfinder.getMaxDegree(), Eq(10));
  
  delete rpoly;
  rpoly = nullptr;
}

TEST(RootFinder, FindRootsSpecifiedInStubForDegreeNine) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(10);

  Roots rootfinder(rpoly);
  std::vector<double> coeff = {1,2,3,4,5,6,7,8,9,10};
  rootfinder.findRoots(coeff);
  
  int degree{0};
  std::vector<double> zr, zi;
  rootfinder.getRoots(degree, zr, zi);

  EXPECT_THAT(zr[0], Eq( 0.065297428539351));
  EXPECT_THAT(zr[1], Eq(-1.0));
  EXPECT_THAT(zr[2], Eq(-2.0));
  EXPECT_THAT(zr[3], Eq(-3.0));
  EXPECT_THAT(zr[4], Eq(-4.0));
  EXPECT_THAT(zr[5], Eq(-0.07));
  EXPECT_THAT(zr[6], Eq( 1.0));
  EXPECT_THAT(zr[7], Eq( 2.0));
  EXPECT_THAT(zr[8], Eq( 3.0));
  EXPECT_THAT(zr[9], Eq( 4.0));

  EXPECT_THAT(zi[0], Eq( 0.0));
  EXPECT_THAT(zi[1], Eq( 0.0));
  EXPECT_THAT(zi[2], Eq( 0.0));
  EXPECT_THAT(zi[3], Eq(-2.0));
  EXPECT_THAT(zi[4], Eq(-2.0));
  EXPECT_THAT(zi[5], Eq( 0.0));
  EXPECT_THAT(zi[6], Eq( 0.0));
  EXPECT_THAT(zi[7], Eq( 0.0));
  EXPECT_THAT(zi[8], Eq( 2.0));
  EXPECT_THAT(zi[9], Eq( 2.0));
  
  delete rpoly;
  rpoly = nullptr;
}

