#include <iostream>
#include "friction_functions.h"

using std::cout;

int main(){

  array<float,2> resultForce = resultantForceOnObject({0,100},{3,3},0.2);

  cout << resultForce[0] << '\n';
  cout << resultForce[1] << '\n';

  cout << "Part 3 - Chapter 14 - Friction\n";

}
