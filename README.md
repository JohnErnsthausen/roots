# roots

Roots is an interface class written in C++ to existing software packages. The interface is built
on the expectation that the existing software will exhaustively exhibit all roots of a polynomial
with real coefficients. The Jenkins-Traub algorithm will accomplish this expectation.

Let's take a look at the interface.
```cpp
class RPoly {
  public:
    int maxDegree;
    int mdp1;
    RPoly(int maxDeg) : maxDegree(maxDeg), mdp1(maxDeg+1) {};
    virtual ~RPoly(void) {};
    virtual void initialize() = 0;
    // rpoly must check degree less than or equal to maxDegree
    // rpoly must check leading coefficient is not zero
    virtual void rpoly(double* op, int degree, double* zeror, double* zeroi) = 0;
};
```
For each software package a solution must override these virtual methods.

## Existing polynomial root-finding software packages

The FORTRAN 77 routine RPOLY.FOR is based on the Jenkins-Traub algorithm. The subroutine is
a polynomial root-finder that exhaustively exhibits all roots of a given polynomial with real coefficients.
Specifically the Jenkins-Traub algorithm exhibits the (complex) roots of the polynomial whose real coefficients
are the elements of the vector C. If C has N+1 components and C(0) is not numerically zero, then the roots
of the polynomial 
```
C(0)*X^N + ... + C(N-1)*X + C(N).
```
are found. RPOLY.FOR is freely available on the NETLIB site as TOMS/493.

RPOLY.FOR is restricted to polynomials with real coefficients of degree 100 or less.
Among other advantages to the implementation in this repository, the code roots eliminates the degree constraint.

Several scientific software developers have ported the FORTRAN 77 code to C++. This class builds on these results
but may (slightly) modify the code to implement the interface.

#### [Rpoly_ak1](http://www.akiti.ca/rpoly_ak1_Intro.html)
Slightly modified the implementation an renamed it Akiti.
Akiti is provided in this github repository.

#### [Rpoly](https://github.com/ebertolazzi/Rpoly) by Enrico Bertolazzi

#### [RPolyPlusPlus](https://github.com/sweeneychris/RpolyPlusPlus) by Chris Sweeney

#### [rpoly.f90](http://jblevins.org/mirror/amiller/rpoly.f90) by Alan Miller

#### [rpoly.cpp](http://www.crbond.com/download/misc/rpoly.cpp)

## Getting started

#### Compiler (on Ubuntu)
```
  > sudo su -
  > apt-get install build-essential
  > apt-get repository ppa:ubuntu-toolchain-r/test
  > apt-get update
  > apt-get install gcc-4.9 g++4.9 cpp-4.9
```
#### CMake
```
  > sudo apt-get install cmake
```
#### Google Mock and Google Test
[Download here](https://github.com/google/googletest).  The environment variable GMOCK_HOME must
be defined.
```
  > export GMOCK_HOME=/path/to/your/installation
```

#### Install the roots class
Put the following files on the include path.
```
#include "rpoly.h"
#include "roots.h"
#include "helper.h"

#include "akiti.h"

```
The header file akiti implements the class as a slight modification of the codes at
[Rpoly_ak1](http://www.akiti.ca/rpoly_ak1_Intro.html).

Other implementations will be tested as my personal research permits or as contributors make
them available to this repository.

### The basic work-flow:
```
mkdir build
cd build
cmake ..
make
```
Then run the executables.

## Getting started with roots
Use the roots class to compute polynomial roots. The code exhibits the roots of the polynomial whose real coefficients
are the elements of the vector C. Here C(0) is not numerically zero. If C has N+1 components, then the polynomial is
```
C(0)*X^N + ... + C(N-1)*X + C(N).
```
Use cases include the following interactions. Use cases are implemented in the Google Mock environment and
tolerances are optimal.

```cpp
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
```

