#include <cassert>
#include "../Programs/geometry_functions.h"

using std::make_pair;

// g++ ex2.cpp ../Programs/geometry_functions.cpp

int main(){

  triangle tr;
  tr.at(0) = make_pair(-4,14);
  tr.at(1) = make_pair(2,2);
  tr.at(2) = make_pair(-10,2);

  point target = make_pair(20,6);

  triangle newTriangle = rotateFollow(tr,target);

  // (4,6)
  assert(std::abs(newTriangle.at(0).first - 4)<1e-5);
  assert(std::abs(newTriangle.at(0).second - 6)<1e-5);

  // (-8,0)
  assert(std::abs(newTriangle.at(1).first - -8)<1e-5);
  assert(std::abs(newTriangle.at(1).second - 0)<1e-5);

  // (-8,12)
  assert(std::abs(newTriangle.at(2).first - -8)<1e-5);
  assert(std::abs(newTriangle.at(2).second - 12)<1e-5);


  // Rotate left
  auto result = rotatePoint(make_pair(4,4),make_pair(8,4),degToRad(90));
  assert(std::abs(result.first-8)<1e-5);
  assert(std::abs(result.second-0)<1e-5);

  // Rotate right
  result = rotatePoint(make_pair(4,4),make_pair(8,4),degToRad(-90));
  assert(std::abs(result.first-8)<1e-5);
  assert(std::abs(result.second-8)<1e-5);

  // Rotate left
  result = rotatePoint(make_pair(5,0),make_pair(0,0),degToRad(90));
  assert(std::abs(result.first - 0)<1e-5);
  assert(std::abs(result.second - 5)<1e-5);

  // Rotate right
  result = rotatePoint(make_pair(5,0),make_pair(0,0),degToRad(-90));
  assert(std::abs(result.first - 0)<1e-5);
  assert(std::abs(result.second - -5)<1e-5);

  // Rotate left
  result = rotatePoint(make_pair(-12,2),make_pair(-4,2),degToRad(90));
  assert(std::abs(result.first - -4)<1e-5);
  assert(std::abs(result.second - -6)<1e-5);

  // Rotate right
  result = rotatePoint(make_pair(-12,2),make_pair(-4,2),degToRad(-90));
  assert(std::abs(result.first - -4)<1e-5);
  assert(std::abs(result.second - 10)<1e-5);

  // Rotate left
  result = rotatePoint(make_pair(4,3),make_pair(0,0),degToRad(90));
  assert(std::abs(result.first - -3)<1e-5);
  assert(std::abs(result.second - 4)<1e-5);

}
