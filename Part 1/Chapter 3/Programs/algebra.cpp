#include "algebra_functions.h"
#include <cassert>
#include <algorithm>

using std::any_of;

// g++ algebra.cpp algebra_functions.cpp ../../Chapter\ 2/Programs/arithmetic_functions.cpp

int main(){

  // x^3 - 6x^2 + 11x - 6
  auto re = solveCubic(-6,11,-6,1);
  assert(re.size()==3);
  assert(any_of(re.begin(),re.end(),compare(1)));
  assert(any_of(re.begin(),re.end(),compare(2)));
  assert(any_of(re.begin(),re.end(),compare(3)));

  // x^3 - 2x^2 - x + 2
  re = solveCubic(-2,-1,2,1);
  assert(re.size()==3);
  assert(any_of(re.begin(),re.end(),compare(1)));
  assert(any_of(re.begin(),re.end(),compare(-1)));
  assert(any_of(re.begin(),re.end(),compare(2)));

  // x^3 - 23x^2 + 142x - 120
  re = solveCubic(-23,142,-120,1);
  assert(re.size()==3);
  assert(any_of(re.begin(),re.end(),compare(1)));
  assert(any_of(re.begin(),re.end(),compare(10)));
  assert(any_of(re.begin(),re.end(),compare(12)));

  // 3x^3 - 16x^2 + 23x - 6
  re = solveCubic(-16,23,-6,3);
  assert(re.size()==3);
  assert(any_of(re.begin(),re.end(),compare(2)));
  assert(any_of(re.begin(),re.end(),compare(3)));
  assert(any_of(re.begin(),re.end(),compare(1.0/3)));

  // 3x^3 - 3x^2 - 90x
  re = solveCubic(-3,-90,0,3);
  assert(re.size()==3);
  assert(any_of(re.begin(),re.end(),compare(0)));
  assert(any_of(re.begin(),re.end(),compare(6)));
  assert(any_of(re.begin(),re.end(),compare(-5)));

  // ----------------------------------------------------------------------

  // 3x + 2y = 2
  // 2x + 5y = 16
  auto sim1 = std::vector<vecflt>({
    vecflt({3, 2, 2}),
    vecflt({2, 5, 16})
  });

  // 3x + 10y = 2
  // 6x + 6y = 14
  auto sim2 = std::vector<vecflt>({
    vecflt({3, 10, 2}),
    vecflt({5, 6, 14})
  });

  // 1x + 3y = 10
  // 5x + -2y = -1
  auto sim3 = std::vector<vecflt>({
    vecflt({1, 3, 10}),
    vecflt({5, -2, -1})
  });

  auto simres = solveSimultaneous(sim1);
  assert(simres.size()==2);
  assert(any_of(simres.begin(),simres.end(),compare(-2)));
  assert(any_of(simres.begin(),simres.end(),compare(4)));

  simres = solveSimultaneous(sim2);
  assert(simres.size()==2);
  assert(any_of(simres.begin(),simres.end(),compare(4)));
  assert(any_of(simres.begin(),simres.end(),compare(-1)));

  simres = solveSimultaneous(sim3);
  assert(simres.size()==2);
  assert(any_of(simres.begin(),simres.end(),compare(1)));
  assert(any_of(simres.begin(),simres.end(),compare(3)));


}
