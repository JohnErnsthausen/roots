#include "gmock/gmock.h"

#include "rpoly.h"
#include <stdexcept>

using namespace testing;

#define DEGREE 10

// START:RPolyStub
class RPolyStub: public RPoly {
  public:
    int maxDegree;
    int mdp1;
    RPolyStub(int degree);
    ~RPolyStub(void);

    void initialize() override;
    void rpoly(double* op, int Degree, double* zeror, double* zeroi) override;
};

RPolyStub::RPolyStub(int degree): RPoly(degree) {
  maxDegree = degree;
  mdp1 = degree+1;
}

RPolyStub::~RPolyStub(void) {}

void RPolyStub::initialize() {}

void RPolyStub::rpoly(double* op, int Degree, double* zeror, double* zeroi) {
  if (op[0]==0.0) {
    throw std::invalid_argument( "The leading coefficient is zero." );
  }
}
// END:RPolyStub

TEST(RpolyInterface, ConstructorPopulatesMaximalDegree) {
  RPolyStub stub(DEGREE);
  ASSERT_THAT(stub.maxDegree, Eq(DEGREE));
}

TEST(RpolyInterface, ConstructorPopulatesMaximalDegreePlusOne) {
  RPolyStub stub(DEGREE);
  ASSERT_THAT(stub.mdp1, Eq(DEGREE+1));
}

TEST(RpolyInterface, HasBaseClassVariableMaxDegree) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(DEGREE);

  ASSERT_THAT(rpoly->maxDegree, Eq(DEGREE));
  
  delete rpoly;
  rpoly = nullptr;
}

TEST(RpolyInterface, HasBaseClassVariableMaxDegreePlusOne) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(DEGREE);

  ASSERT_THAT(rpoly->mdp1, Eq(DEGREE+1));
  
  delete rpoly;
  rpoly = nullptr;
}

TEST(RpolyInterface, ExceptionThrownForLeadingCoefficientOfZero) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(DEGREE);

  double* op{nullptr};
  double* zr{nullptr};
  double* zi{nullptr};
  op = new double[DEGREE+1];
  zr = new double[DEGREE];
  zi = new double[DEGREE];

  try {
    op[0] = 0.0;
    rpoly->rpoly(op,DEGREE,zr,zi);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& expected) {
    ASSERT_STREQ(expected.what(),"The leading coefficient is zero.");
  }

  delete [] op;
  delete [] zr;
  delete [] zi;
  delete rpoly;
  op = nullptr;
  zr = nullptr;
  zi = nullptr;
  rpoly = nullptr;
}

TEST(RpolyInterface, ExceptionThrownForExceedingMaximalDegree) {
  RPoly* rpoly{nullptr};
  rpoly = new RPolyStub(DEGREE);

  double* op{nullptr};
  double* zr{nullptr};
  double* zi{nullptr};
  op = new double[DEGREE+1];
  zr = new double[DEGREE];
  zi = new double[DEGREE];

  try {
    rpoly->rpoly(op,DEGREE+1,zr,zi);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& expected) {
    ASSERT_STREQ(expected.what(),"Requested maximal degree is greater than MAXDEGREE.");
  }

  delete [] op;
  delete [] zr;
  delete [] zi;
  delete rpoly;
  op = nullptr;
  zr = nullptr;
  zi = nullptr;
  rpoly = nullptr;
}

