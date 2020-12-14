#include "../Programs/algebra_functions.h"
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

// g++ ex1.cpp ../Programs/algebra_functions.cpp ../../Chapter\ 2/Programs/arithmetic_functions.cpp

int main(){
  
  //assert(substituteX("x",6)=="6");
//   assert(substituteX("5x",6)=="30");
//   assert(substituteX("12x",5)=="60");
//   assert(substituteX("3x(7*2)",3)=="9(7*2)");
//   assert(substituteX("(x-(2x*x))(x+x)^(2x-x)",5)=="(5-(10*5))(5+5)^(10-5)");
  
  substituteNoX("(5-2)(5+5)(10-5)");
  
  //cout << addSub("5+2-4+7") << endl;
  
  // multiplication, powers
  
  cout << onlyMulDiv("2*3*4*5",1);

}
