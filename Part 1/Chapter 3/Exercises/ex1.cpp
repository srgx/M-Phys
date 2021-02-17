#include "../Programs/algebra_functions.h"
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

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
  
  
  // Exponentiation in expression consisting
  // only of numbers and symbols '^', '+', '-', '*', '/'
  assert(expo("6+2^3-9+4^2")=="6+8-9+16");
  assert(expo("6+2^3*4-9+1^2^3/7-5")=="6+8*4-9+1/7-5");
  assert(expo("3^3*4/5*2^1/8")=="27*4/5*2/8");

  assert(substituteNoX("(5-2)(5+5)(10-5)")=="150");
  assert(substituteNoX("(5^3-4)/2")=="60");
  assert(substituteNoX("2^((6-4)/(6-5))")=="4");

  assert(substitute("(x-2)(x+5)(2x-x)",5)==150);
  assert(substitute("(x+(2x*x))(x+x)(2x-x)",5)==2750);
  assert(substitute("x^3*2-x^2",5)==225);
  
  // Tests from book
  
  assert(substitute("5x+3",7)==38);
  assert(substitute("5x+3",4)==23);
  
  assert(substitute("4-2(x-5)",7)==0);
  assert(substitute("4-2(x-5)",9)==-4);
  
  assert(substitute("(x^3-4)/2",4)==30);
  assert(substitute("(x^3-4)/2",5)==60);
  
  assert(substitute("2^((x-4)/(x-5))",6)==4);
  assert(substitute("2^((x-4)/(x-5))",10)==2);
  
  std::cout << "Exit\n";

}
