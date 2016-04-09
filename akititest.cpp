#include "gmock/gmock.h"

#include "rpoly.h"
#include "akiti.h"
#include "roots.h"
#include "helper.h"

#include <vector>
#include <stdexcept>

using namespace testing;

class RootFinder: public Test {
  public:
    RPoly* rpoly01{nullptr};
    RPoly* rpoly10{nullptr};
    std::vector<double> coeff = {0.001388888888889,
                                 0.008333333333333,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 -0.000000010000000
                                };

    void SetUp() override {
      rpoly01 = new Akiti(1);
      rpoly10 = new Akiti(10);
    }

    void TearDown() override {
      delete rpoly01;
      rpoly01 = nullptr;
      delete rpoly10;
      rpoly10 = nullptr;
    }
};

TEST_F(RootFinder, GetMaximalDegree) {
  Roots rootfinder(rpoly10);
  ASSERT_THAT(rootfinder.getMaxDegree(), Eq(10));
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
    ASSERT_STREQ(expected.what(),
        "Requested maximal degree is greater than MAXDEGREE.");
  }
}

TEST_F(RootFinder, GetAbsMinimalRealRoot) {
  Roots rootfinder(rpoly10);
  rootfinder.findRoots(coeff);

  // Compare to MatLab result
  Helper helper;
  ASSERT_TRUE(helper.nearly_equal(rootfinder.getAbsMinRealRoot(),
        0.065297428539350, 100));
}

TEST_F(RootFinder, GetMinimalPositiveRealRoot) {
  Roots rootfinder(rpoly10);
  rootfinder.findRoots(coeff);

  // Compare to MatLab result
  Helper helper;
  ASSERT_TRUE(helper.nearly_equal(rootfinder.getMinPosRealRoot(),
        0.065297428539350, 100));
}

TEST_F(RootFinder, GetMaximalPositiveRealRoot) {
  Roots rootfinder(rpoly10);
  rootfinder.findRoots(coeff);

  // Compare to MatLab result
  Helper helper;
  ASSERT_TRUE(helper.nearly_equal(rootfinder.getMaxPosRealRoot(),
        0.065297428539350, 100));
}

TEST_F(RootFinder, GetMinimalNegativeRealRoot) {
  Roots rootfinder(rpoly10);
  rootfinder.findRoots(coeff);

  // Compare to MatLab result
  Helper helper;
  ASSERT_TRUE(helper.nearly_equal(rootfinder.getMinNegRealRoot(),
        -6.000000000925208, 100));
}

TEST_F(RootFinder, GetMaximalNegativeRealRoot) {
  Roots rootfinder(rpoly10);
  rootfinder.findRoots(coeff);

  // Compare to MatLab result
  Helper helper;
  ASSERT_TRUE(helper.nearly_equal(rootfinder.getMaxNegRealRoot(),
        -6.000000000925208, 100));
}

TEST_F(RootFinder, AllRealRootExample) {
  Roots rootfinder(rpoly10);
  std::vector<double> c = {
    1,
    -55,
    1320,
    -18150,
    157773,
    -902055,
    3416930,
    -8409500,
    12753576,
    -10628640,
    3628800
  };
  rootfinder.findRoots(c);

  int nRealRoot;
  std::vector<double> zr;
  rootfinder.getRoots(nRealRoot, zr);

  // Compare to MatLab result: Ill conditioned problem!
  // Roots are like 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
  Helper helper;

  EXPECT_THAT(nRealRoot, Eq(10));
  EXPECT_TRUE(helper.nearly_equal(rootfinder.getMaxPosRealRoot(),
        10.000000000328654, 1000000));
  EXPECT_TRUE(helper.nearly_equal(rootfinder.getMinPosRealRoot(),
         1.0, 1));
}

