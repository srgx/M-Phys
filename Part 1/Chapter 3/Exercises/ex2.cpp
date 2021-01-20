#include <iostream>
#include <cassert>
#include "../Programs/algebra_functions.h"

// g++ ex2.cpp ../Programs/algebra_functions.cpp ../../Chapter\ 2/Programs/arithmetic_functions.cpp && ./a.out

int main(){
  
  assert(countX("22x+19+13x-3x-6+2")==32);
  assert(countX("22x+19+13x-3x-6+2x")==34);
  
  assert(countNums("22x+19+13x-3x-6+2+7x")==15);
  assert(countNums("5x+23+21x+7x-3+2")==22);
  
  assert(groupTerms("22x+19+13x-3x-6+2+7x")=="39x+15");
  
}
