# roots

Roots is an interface written in C++ to existing software packages that exhaustively exhibit
all roots of a polynomial with real coefficients.

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
are the elements of the vector C. If C has N+1 components and C(0) is not zero, then the roots of the polynomial 
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

The basic work-flow:
```
mkdir build
cd build
cmake ..
make
```

## Getting started with roots
Use roots to compute polynomial roots. The code exhibits the roots of the polynomial whose real coefficients
are the elements of the vector C. If C has N+1 components, then the polynomial is
```
C(0)*X^N + ... + C(N-1)*X + C(N).
```
Use cases include the following interactions.

```cpp
#include "roots.h"
#include "helper.h"

#include <vector>

int main() {

  RPoly* rpoly{nullptr};
  rpoly = new Akiti(10);
  
  // Get maximal degree
  Roots rootfinder(rpoly);
  ASSERT_THAT(rootfinder.getMaxDegree(), Eq(10));
  
  
  // Specifies value of degree
  std::vector<double> coeff = {1,2,3};
  rootfinder.findRoots(coeff);
  ASSERT_THAT(rootfinder.getDegree(), Eq(2));
  
  // Evaluates the absolute minimum of real roots
  std::vector<double> coeff = {0.001388888888889, 0.008333333333333, 0.0, 0.0, 0.0, 0.0, -0.000000010000000};
  rootfinder.findRoots(coeff);
  // Compare to MatLab result
  Helper helper;
  ASSERT_TRUE(helper.nearly_equal(rootfinder.getAbsMin(), 0.065297428539350, 100));
  
  delete rpoly;
  rpoly = nullptr;

  return 0;
}
```

