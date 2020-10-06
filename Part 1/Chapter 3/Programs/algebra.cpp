#include "functions.h"
#include <cassert>

// g++ algebra.cpp functions.cpp

int main(){
  assert(solveCubic(1,2,3,4) == vecflt{ 69 });
}
