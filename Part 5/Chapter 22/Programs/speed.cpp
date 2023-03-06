#include <iostream>
#include <cassert>
#include "speed_functions.h"

using std::cout;

int main(){

  assert(12 == sillyAdd(5,7));

  ps2d pts = drawBresenham({0,2},{3,1});

  for(const i2 & p : pts){
    cout << p[0] << ", " << p[1] << '\n';
  }

  cout << "Part 5 - Chapter 22 - Speed\n";

}
