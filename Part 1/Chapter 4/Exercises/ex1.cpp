#include <iostream>
#include <array>
#include <cassert>
#include "../Programs/geometry_functions.h"

using std::cout; using std::endl;

// g++ ex1.cpp ../Programs/geometry_functions.cpp

int main(){

  // 3 sides

  assert(compareAprox(solveTriangle
        (triangleInfo({ 3, 4, 5, -1, -1, -1 })),
         triangleInfo({ 3, 4, 5, 36.87, 53.13, 90 })));

  assert(compareAprox(solveTriangle
        (triangleInfo({ 3, 4, 4, -1, -1, -1 })),
         triangleInfo({ 3, 4, 4, 44.05, 67.98, 67.98 })));

  assert(compareAprox(solveTriangle
        (triangleInfo({ 3, 3, 3, -1, -1, -1 })),
         triangleInfo({ 3, 3, 3, 60, 60, 60 })));

  assert(compareAprox(solveTriangle
        (triangleInfo({ 3, 3, 3, 60, 60, 60 })),
         triangleInfo({ 3, 3, 3, 60, 60, 60 })));

  assert(compareAprox(solveTriangle
        (triangleInfo({ 13.4, 9.1, 16.5, 54.1, 33.6, 92.3 })),
         triangleInfo({ 13.4, 9.1, 16.5, 54.1, 33.6, 92.3 })));


  // 2 angles and 1 side

  assert(compareAprox(solveTriangle
        (triangleInfo({ -1, -1, 4, 44.05, 67.98, -1 })),
         triangleInfo({ 3, 4, 4, 44.05, 67.98, 67.98 })));

  assert(compareAprox(solveTriangle
        (triangleInfo({ -1, -1, 16.5, 54.1, -1, 92.3 })),
         triangleInfo({ 13.4, 9.1, 16.5, 54.1, 33.6, 92.3 })));

  assert(compareAprox(solveTriangle
        (triangleInfo({ -1, -1, 16.5, -1, 33.6, 92.3 })),
         triangleInfo({ 13.4, 9.1, 16.5, 54.1, 33.6, 92.3 })));

  assert(compareAprox(solveTriangle
        (triangleInfo({ 13.4, -1, -1, 54.1, -1, 92.3 })),
         triangleInfo({ 13.4, 9.1, 16.5, 54.1, 33.6, 92.3 })));


  // 2 sides and angle between them

  assert(compareAprox(solveTriangle
        (triangleInfo({ 13.4, 9.1, -1, -1, -1, 92.3 })),
         triangleInfo({ 13.4, 9.1, 16.5, 54.1, 33.6, 92.3 })));

  auto tst = solveTriangle(triangleInfo({ 13.4, 9.1, -1, -1, -1, 92.3 }));

  for(const auto & v : tst){
    cout << v << "|";
  }


  cout << endl;

  // assert(compareAprox(solveTriangle
  //       (triangleInfo({ 3, -1, 4, -1, 67.98, -1 })),
  //        triangleInfo({ 3, 4, 4, 44.05, 67.98, 67.98 })));




}
