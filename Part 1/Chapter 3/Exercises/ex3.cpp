#include <iostream>
#include <cassert>
#include <algorithm>
#include "../Programs/algebra_functions.h"

int main(){

  // 4x + y = 7
  // 3x + 2y = 9
  auto linear = std::vector<vecflt>({
    vecflt({4, 1, 7}),
    vecflt({3, 2, 9})
  });

  // x^2 - 6x + 9
  auto quadratic1 = std::vector<vecflt>({
    vecflt({1, -6, 9})
  });

  // x^2 + x + 5
  auto quadratic2 = std::vector<vecflt>({
    vecflt({1, 1, 3})
  });

  // 4x^2 + 26x + 12
  auto quadratic3 = std::vector<vecflt>({
    vecflt({4, 26, 12})
  });

  const float d = 1e-5;

  eqResult result = solve(linear);

  assert(result.success);
  vecflt answer = result.answer;
  assert(answer.size()==2);
  assert(std::abs(answer.at(0) - 1)<d);
  assert(std::abs(answer.at(1) - 3)<d);

  // 1 solution
  result = solve(quadratic1);
  assert(result.success);
  answer = result.answer;
  assert(answer.size()==1);
  assert(std::abs(answer.at(0) - 3)<d);

  // No solution
  result = solve(quadratic2);
  assert(!result.success);
  answer = result.answer;
  assert(answer.size()==0);

  // 2 solutions
  result = solve(quadratic3);
  assert(result.success);
  answer = result.answer;
  assert(answer.size()==2);
  assert(any_of(answer.begin(),answer.end(),compare(-6)));
  assert(any_of(answer.begin(),answer.end(),compare(-0.5)));

  std::cout << "Part 1 - Chapter 3 - Exercise 3\n";

}
