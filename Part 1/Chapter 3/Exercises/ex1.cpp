#include "../Programs/algebra_functions.h"
#include <cassert>
#include <iostream>

// g++ ex1.cpp ../Programs/algebra_functions.cpp ../../Chapter\ 2/Programs/arithmetic_functions.cpp

int main(){

  assert(isExp("x"));
  assert(isExp("5x"));
  assert(isExp("25x"));

  assert(substitute("x",6)==6);
  assert(substitute("3x",9)==27);
  assert(substitute("25x",4)==100);
  assert(substitute("5x+35",8)==75);
  assert(substitute("6x+2+x",5)==37);
  assert(substitute("12+4x+2x+8",2)==32);

  assert(getSubexpFrom("5x-10-2",0)=="5x");
  assert(getSubexpFrom("5x-10-2",3)=="10");
  assert(getSubexpFrom("10-12x-25x",3)=="12x");

  assert(substitute("5x-10-2",6)==18);
  assert(substitute("5x-10-2-x",6)==12);
  assert(substitute("56-4x+20",2)==68);

  //assert(substitute("4-2(x-5)",7)==0);
  //std::cout << substitute("4-2(x-5)+1",7) << std::endl;
  //std::cout << getSubexpFrom("4-2((x-5))+1",2) << std::endl;

  assert(isParExp("(4+6)"));
  assert(isParExp("5(7-2)"));

}
