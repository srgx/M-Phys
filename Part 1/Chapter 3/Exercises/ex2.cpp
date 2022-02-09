#include <iostream>
#include <cassert>
#include "../Programs/algebra_functions.h"

int main(){
  
  assert(countX("22x+19+13x-3x-6+2")==32);
  assert(countX("22x+19+13x-3x-6+2x")==34);
  
  assert(countNums("22x+19+13x-3x-6+2+7x")==15);
  assert(countNums("5x+23+21x+7x-3+2")==22);
  
  assert(simplify("22x+19+13x-3x-6+2+7x")=="39x+15");
  
  std::cout << "Part 1 - Chapter 3 - Exercise 2\n";
  
}
