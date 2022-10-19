#include "geometry_functions.h"
#include <cmath>
#include <cassert>
#include <iostream>

int main(){

  const float X = 12; const float Y = 7;
  const float D = 1e-7;

  assert(std::abs(pow(sin(X),2) + pow(cos(X),2)-1)<D);
  assert(std::abs(sin(X+Y)-(sin(X)*cos(Y)+cos(X)*sin(Y)))<D);
  assert(std::abs(cos(X+Y)-(cos(X)*cos(Y)-sin(X)*sin(Y)))<D);
  assert(std::abs(tan(X+Y)-(tan(X)+tan(Y))/(1-(tan(X)*tan(Y))))<D);
  assert(std::abs(sin(2*X)-(2*sin(X)*cos(X)))<D);
  assert(std::abs(cos(2*X)-(pow(cos(X),2)-pow(sin(X),2)))<D);
  assert(std::abs(tan(2*X)-(2*tan(X)/(1-pow(tan(X),2))))<D);

  std::cout << "Part 1 - Chapter 4 - Geometry\n";
}
