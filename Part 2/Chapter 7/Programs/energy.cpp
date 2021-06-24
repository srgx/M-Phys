#include <iostream>
#include <cassert>
#include "energy_functions.h"

using std::cout;
using std::endl;

int main(){

  // Initial speed, acceleration, time
  assert(distanceAcceleration(5,2,5)==50);
  assert(speedAcceleration(5,2,5)==15);

  cout << "Energy\n";
  cout << "Part 2 - Chapter 7 - Energy\n";

}
