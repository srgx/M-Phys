#include <iostream>
#include <array>
#include <cassert>
#include "../Programs/geometry_functions.h"

using std::cout; using std::endl;

int main(){

  // for(const auto & v : result){
  //   cout << v << "|";
  // }
  //
  // cout << endl;


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


  // 2 angles and 1 side

  
}
