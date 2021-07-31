#include <iostream>
#include "resolution_functions.h"

int main(){

  vf initialVelocity = {3, 3};
  vf normal = {-3,3};

  vf newVelocity =
    resolveFixedCollision(initialVelocity,normal);

  std::cout << "Part 2 - Chapter 9 - Resolution\n";
}
