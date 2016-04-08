#include "gmock/gmock.h"

#include "rpoly.h"
#include "rpolystub.h"
#include "roots.h"

#include <vector>
#include <stdexcept>

using namespace testing;

#define DEGREE 10

class RootFinder: public Test {
  public:
    RPoly* rpoly01{nullptr};
    RPoly* rpoly10{nullptr};

    void SetUp() override {
      rpoly01 = new RPolyStub(1);
      rpoly10 = new RPolyStub(DEGREE);
    }

    void TearDown() override {
      delete rpoly01;
      rpoly01 = nullptr;
      delete rpoly10;
      rpoly10 = nullptr;
    }
};

TEST_F(RootFinder, GetMaximalDegreeFromStub) {
  Roots rootfinder(rpoly10);
  ASSERT_THAT(rootfinder.getMaxDegree(), Eq(DEGREE));
}

TEST_F(RootFinder, FindRootsSpecifiedInStubForDegreeNine) {
  Roots rootfinder(rpoly10);
  std::vector<double> coeff = {1,2,3,4,5,6,7,8,9,10};
  rootfinder.findRoots(coeff);
  
  int degree;
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
}

TEST_F(RootFinder, SpecifiesValueOfDegree) {
  Roots rootfinder(rpoly10);
  std::vector<double> coeff = {1,2,3};
  rootfinder.findRoots(coeff);

  int degree;
  std::vector<double> zr, zi;
  rootfinder.getRoots(degree, zr, zi);

  ASSERT_THAT(degree, Eq(2));
}

TEST_F(RootFinder, UncaughtExceptionThrownForLeadingCoefficientOfZero) {
  Roots rootfinder(rpoly10);
  try {
    std::vector<double> coeff = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
    rootfinder.findRoots(coeff);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& expected) {
    ASSERT_STREQ(expected.what(),"The leading coefficient is zero.");
  }
}

TEST_F(RootFinder, UncaughtExceptionThrownForExceedingMaximalDegree) {
  Roots rootfinder(rpoly01);
  try {
    std::vector<double> coeff = {1.0, 2.0, 3.0};
    rootfinder.findRoots(coeff);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& expected) {
    ASSERT_STREQ(expected.what(),"Requested maximal degree is greater than MAXDEGREE.");
  }
}

TEST_F(RootFinder, GetAbsMinimalRealRoot) {
  Roots rootfinder(rpoly10);
  std::vector<double> coeff = {1,2,3,4,5,6,7,8,9,10};
  rootfinder.findRoots(coeff);

  ASSERT_THAT(rootfinder.getAbsMinRealRoot(), Eq(0.065297428539351));
}


