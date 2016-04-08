#include "gmock/gmock.h"

#include "rpoly.h"
#include "rpolystub.h"

using namespace testing;

#define DEGREE 10

class RpolyInterface: public Test {
  public:
    RPoly* rpoly{nullptr};
    double* op{nullptr};
    double* zr{nullptr};
    double* zi{nullptr};

    void SetUp() override {
      rpoly = new RPolyStub(DEGREE);
      op = new double[DEGREE+1];
      zr = new double[DEGREE];
      zi = new double[DEGREE];
    }

    void TearDown() override {
      delete [] op;
      delete [] zr;
      delete [] zi;
      op = nullptr;
      zr = nullptr;
      zi = nullptr;
      delete rpoly;
      rpoly = nullptr;
    }
};

TEST_F(RpolyInterface, ConstructorPopulatesMaximalDegree) {
  RPolyStub stub(DEGREE);
  ASSERT_THAT(stub.maxDegree, Eq(DEGREE));
}

TEST_F(RpolyInterface, ConstructorPopulatesMaximalDegreePlusOne) {
  RPolyStub stub(DEGREE);
  ASSERT_THAT(stub.mdp1, Eq(DEGREE+1));
}

TEST_F(RpolyInterface, HasBaseClassVariableMaxDegree) {
  ASSERT_THAT(rpoly->maxDegree, Eq(DEGREE));
}

TEST_F(RpolyInterface, HasBaseClassVariableMaxDegreePlusOne) {
  ASSERT_THAT(rpoly->mdp1, Eq(DEGREE+1));
}

TEST_F(RpolyInterface, ExceptionThrownForLeadingCoefficientOfZero) {
  try {
    op[0] = 0.0;
    rpoly->rpoly(op,DEGREE,zr,zi);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& expected) {
    ASSERT_STREQ(expected.what(),"The leading coefficient is zero.");
  }
}

TEST_F(RpolyInterface, ExceptionThrownForExceedingMaximalDegree) {
  try {
    rpoly->rpoly(op,DEGREE+1,zr,zi);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& expected) {
    ASSERT_STREQ(expected.what(),"Requested maximal degree is greater than MAXDEGREE.");
  }
}

