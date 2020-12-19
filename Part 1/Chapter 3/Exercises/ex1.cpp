#include "../Programs/algebra_functions.h"
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

// g++ ex1.cpp ../Programs/algebra_functions.cpp ../../Chapter\ 2/Programs/arithmetic_functions.cpp

int main(){

  // Substitute variable x
  assert(substituteX("x",6)=="6");
  assert(substituteX("5x",6)=="30");
  assert(substituteX("12x",5)=="60");
  assert(substituteX("3x(7*2)",3)=="9(7*2)");
  assert(substituteX("(x-(2x*x))(x+x)^(2x-x)",5)=="(5-(10*5))(5+5)^(10-5)");

  // Substitute parentheses at first level
  assert(substituteParens("(5-2)(5+5)(10-5)")=="3*10*5");
  assert(substituteParens("7*(7*8)+9")=="7*56+9");
  assert(substituteParens("6+(5*(4-2))")=="6+10");


  // Multiplication and division in expression consisting
  // only of numbers and symbols '+', '-', '*', '/'
  assert(mulDiv("2*3*4*5+1-5*6+8")==("120+1-30+8"));
  assert(mulDiv("5*8-2*16-2")=="40-32-2");
  assert(mulDiv("16/2+100/4-33*2")=="8+25-66");


  assert(substituteNoX("(5-2)(5+5)(10-5)")=="150");

  // Substitute variable, remove parentheses,
  // multiply and divide, add and subtract
  assert(substitute("(x-2)(x+5)(2x-x)",5)==150);
  assert(substitute("(x+(2x*x))(x+x)(2x-x)",5)==2750);

}
