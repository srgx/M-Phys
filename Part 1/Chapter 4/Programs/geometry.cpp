#include "functions.h"
#include <cmath>
#include <cassert>

// g++ geometry.cpp functions.cpp

int main(){

  const float X = 12; const float Y = 7;
  const float D = 1e-7;

  assert(abs(pow(sin(X),2) + pow(cos(X),2)-1)<D);
  assert(abs(sin(X+Y)-(sin(X)*cos(Y)+cos(X)*sin(Y)))<D);
  assert(abs(cos(X+Y)-(cos(X)*cos(Y)-sin(X)*sin(Y)))<D);
  assert(abs(tan(X+Y)-(tan(X)+tan(Y))/(1-(tan(X)*tan(Y))))<D);
  assert(abs(sin(2*X)-(2*sin(X)*cos(X)))<D);
  assert(abs(cos(2*X)-(pow(cos(X),2)-pow(sin(X),2)))<D);
  assert(abs(tan(2*X)-(2*tan(X)/(1-pow(tan(X),2))))<D);
}
