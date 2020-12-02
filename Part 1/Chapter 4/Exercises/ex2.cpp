#include <cassert>
#include "../Programs/geometry_functions.h"
#include <iostream>

using std::make_pair;

// g++ ex2.cpp ../Programs/geometry_functions.cpp

using std::cout;

int main(){

  const float D = 0.1;

  // ---------------------------------------------------------------------------

  // Rotate CCW (4,4) around (8,4)
  auto result = rotatePoint(make_pair(4,4),make_pair(8,4),degToRad(90));

  // (8,0)
  assert(std::abs(result.first-8)<D);
  assert(std::abs(result.second-0)<D);

  // ---------------------------------------------------------------------------

  // Rotate CW (4,4) around (8,4)
  result = rotatePoint(make_pair(4,4),make_pair(8,4),degToRad(-90));

  // (8,8)
  assert(std::abs(result.first-8)<D);
  assert(std::abs(result.second-8)<D);

  // ---------------------------------------------------------------------------

  // Rotate CCW (5,0) around (0,0)
  result = rotatePoint(make_pair(5,0),make_pair(0,0),degToRad(90));

  // (0,5)
  assert(std::abs(result.first - 0)<D);
  assert(std::abs(result.second - 5)<D);

  // ---------------------------------------------------------------------------

  // Rotate CW (5,0) around (0,0)
  result = rotatePoint(make_pair(5,0),make_pair(0,0),degToRad(-90));

  // (0,-5)
  assert(std::abs(result.first - 0)<D);
  assert(std::abs(result.second - -5)<D);

  // ---------------------------------------------------------------------------

  // Rotate CCW (-12,2) around (-4,2)
  result = rotatePoint(make_pair(-12,2),make_pair(-4,2),degToRad(90));

  // (-4,-6)
  assert(std::abs(result.first - -4)<D);
  assert(std::abs(result.second - -6)<D);

  // ---------------------------------------------------------------------------

  // Rotate CW (-12,2) around (-4,2)
  result = rotatePoint(make_pair(-12,2),make_pair(-4,2),degToRad(-90));

  // (-4,10)
  assert(std::abs(result.first - -4)<D);
  assert(std::abs(result.second - 10)<D);

  // ---------------------------------------------------------------------------

  // Rotate CCW (4,3) around (0,0)
  result = rotatePoint(make_pair(4,3),make_pair(0,0),degToRad(90));

  // (-3,4)
  assert(std::abs(result.first - -3)<D);
  assert(std::abs(result.second - 4)<D);

  // ---------------------------------------------------------------------------

  // Rotate CW (0,0) around (5,5)
  result = rotatePoint(make_pair(0,0),make_pair(5,5),degToRad(-180));

  // (10,10)
  assert(std::abs(result.first - 10)<D);
  assert(std::abs(result.second - 10)<D);

  // ---------------------------------------------------------------------------

  // Rotate CCW (5,5) around (0,10)
  result = rotatePoint(make_pair(5,5),make_pair(0,10),degToRad(45));

  // (7,10)
  assert(std::abs(result.first - 7)<D);
  assert(std::abs(result.second - 10)<D);

  // ---------------------------------------------------------------------------

  // Rotate CW (5,5) around (0,10)
  result = rotatePoint(make_pair(5,5),make_pair(0,10),degToRad(-45));

  // (0,3)
  assert(std::abs(result.first - 0)<D);
  assert(std::abs(result.second - 3)<D);

  // ---------------------------------------------------------------------------

  // Rotate triangle towards target

  triangle tr;
  tr.at(0) = make_pair(-4,14);
  tr.at(1) = make_pair(2,2);
  tr.at(2) = make_pair(-10,2);


  // Rotate CW 90 around (-4,6)
  point target = make_pair(20,6);
  triangle newTriangle = rotateFollow(tr,target);

  // (4,6)
  assert(std::abs(newTriangle.at(0).first - 4)<D);
  assert(std::abs(newTriangle.at(0).second - 6)<D);

  // (-8,0)
  assert(std::abs(newTriangle.at(1).first - -8)<D);
  assert(std::abs(newTriangle.at(1).second - 0)<D);

  // (-8,12)
  assert(std::abs(newTriangle.at(2).first - -8)<D);
  assert(std::abs(newTriangle.at(2).second - 12)<D);

  // ---------------------------------------------------------------------------

  // Rotate CCW 45 around (-4,6)
  target = make_pair(-12,14);
  newTriangle = rotateFollow(tr,target);

  // (-9.66,11.66)
  assert(std::abs(newTriangle.at(0).first - -9.66)<D);
  assert(std::abs(newTriangle.at(0).second - 11.66)<D);

  // (3.07,7.41)
  assert(std::abs(newTriangle.at(1).first - 3.07)<D);
  assert(std::abs(newTriangle.at(1).second - 7.41)<D);

  // (-5.41,-1.07)
  assert(std::abs(newTriangle.at(2).first - -5.41)<D);
  assert(std::abs(newTriangle.at(2).second - -1.07)<D);

  // ---------------------------------------------------------------------------

  // Rotate CW 45 around (-4,6)
  target = make_pair(6,16);
  newTriangle = rotateFollow(tr,target);

  // (1.66,11.66)
  assert(std::abs(newTriangle.at(0).first - 1.66)<D);
  assert(std::abs(newTriangle.at(0).second - 11.66)<D);

  // (-2.59,-1.07)
  assert(std::abs(newTriangle.at(1).first - -2.59)<D);
  assert(std::abs(newTriangle.at(1).second - -1.07)<D);

  // (-11.07,7.41)
  assert(std::abs(newTriangle.at(2).first - -11.07)<D);
  assert(std::abs(newTriangle.at(2).second - 7.41)<D);

  // ---------------------------------------------------------------------------

  // Rotate CW 135 around (-4,6)
  target = make_pair(-2,4);
  newTriangle = rotateFollow(tr,target);

  // (1.66,0.34)
  assert(std::abs(newTriangle.at(0).first - 1.66)<D);
  assert(std::abs(newTriangle.at(0).second - 0.34)<D);

  // (-11.07,4.59)
  assert(std::abs(newTriangle.at(1).first - -11.07)<D);
  assert(std::abs(newTriangle.at(1).second - 4.59)<D);

  // (-2.59,13.07)
  assert(std::abs(newTriangle.at(2).first - -2.59)<D);
  assert(std::abs(newTriangle.at(2).second - 13.07)<D);

  // ---------------------------------------------------------------------------

  // Rotate CCW 135 around (-4,6)
  target = make_pair(-12,-2);
  newTriangle = rotateFollow(tr,target);

  // (-9.66,0.34)
  assert(std::abs(newTriangle.at(0).first - -9.66)<D);
  assert(std::abs(newTriangle.at(0).second - 0.34)<D);

  // (-5.41,13.07)
  assert(std::abs(newTriangle.at(1).first - -5.41)<D);
  assert(std::abs(newTriangle.at(1).second - 13.07)<D);

  // (3.07,4.59)
  assert(std::abs(newTriangle.at(2).first - 3.07)<D);
  assert(std::abs(newTriangle.at(2).second - 4.59)<D);

  // ---------------------------------------------------------------------------

  // Rotate 0 around (-4,6)
  target = make_pair(-4,20);
  newTriangle = rotateFollow(tr,target);

  // (-4,14)
  assert(std::abs(newTriangle.at(0).first - -4)<D);
  assert(std::abs(newTriangle.at(0).second - 14)<D);

  // (2,2)
  assert(std::abs(newTriangle.at(1).first - 2)<D);
  assert(std::abs(newTriangle.at(1).second - 2)<D);

  // (-10,2)
  assert(std::abs(newTriangle.at(2).first - -10)<D);
  assert(std::abs(newTriangle.at(2).second - 2)<D);

  // ---------------------------------------------------------------------------

  // Rotate CCW 180 around (-4,6)
  target = make_pair(-4,-20);
  newTriangle = rotateFollow(tr,target);

  // (-4,-2)
  assert(std::abs(newTriangle.at(0).first - -4)<D);
  assert(std::abs(newTriangle.at(0).second - -2)<D);

  // (-10,10)
  assert(std::abs(newTriangle.at(1).first - -10)<D);
  assert(std::abs(newTriangle.at(1).second - 10)<D);

  // (2,10)
  assert(std::abs(newTriangle.at(2).first - 2)<D);
  assert(std::abs(newTriangle.at(2).second - 10)<D);


  cout << "Exit\n";

}
