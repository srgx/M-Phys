#include <iostream>
#include <cassert>
#include "geometry3d_functions.h"

using std::cout;
using std::endl;

int main(){

  const float d = 1e-3;

  assert (negate3d ({6,-22,7}) == vector3d ({-6,22,-7}));

  assert (add3d ({6,12,8},{8,33,123}) == vector3d ({14,45,131}));

  assert (sub3d ({87,23,44},{-6,56,2}) == vector3d ({93,-33,42}));

  assert (std::abs (magnitude3d ({5,44,12}) - 45.88) < d);

  assert (std::abs (dot3d ({1,2,3},{1,5,7}) - 32) < d);

  assert (magnitude3d (unit3d ({54,33,123})) == 1);

  assert (crossProduct ({-1,-2,3}, {4,0,-8}) == vector3d ({16,4,8}));

  assert (crossProduct ({99,88,77}, {99,88,77}) == vector3d ({0,0,0}));

  cout << "Part 4 - Chapter 17 - Geometry 3D\n";

}
