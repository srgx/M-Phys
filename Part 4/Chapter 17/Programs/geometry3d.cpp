#include <iostream>
#include <cassert>
#include "geometry3d_functions.h"

using std::cout;
using std::endl;

int main(){

  const float d = 1e-3;

  assert (std::abs (magnitude3d (vector3d ({5,44,12})) - 45.88) < d);

  assert (std::abs (dot3d (vector3d ({1,2,3}),
                           vector3d ({1,5,7})) - 32) < d);

  assert (magnitude3d (unit3d (vector3d ({54,33,123}))) == 1);

  assert (crossProduct (vector3d ({-1,-2,3}),
                        vector3d ({4,0,-8})) ==
         vector3d ({16,4,8}));

  cout << "Part 4 - Chapter 17 - Geometry 3D\n";

}
