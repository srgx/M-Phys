#include <iostream>
#include <cassert>
#include "collisions_functions.h"

using std::cout;

int main(){

  cout << "\n***Circle Data***\n\n";

  vf circleCenter = {0,0}; float circleRadius = 10;

  cout << "Circle center: (" << circleCenter[0] << "," << circleCenter[1] << ")\n";
  cout << "Circle radius: " << circleRadius << "\n";

  cout << "\n***Moving Circle and Wall***\n\n";

  vf circleVector = {50,-50}; vf wallOrigin  = {100,20}; vf wallVector = {-1,-1};

  cout << "Circle displacement vector: (" <<
           circleVector[0] << "," << circleVector[1] << ")\n";
  cout << "Wall point: (" << wallOrigin[0] << "," << wallOrigin[1] << ")\n";
  cout << "Wall vector: (" << wallVector[0] << "," << wallVector[1] << ")\n";

  circle aCircle(circleCenter,circleVector,circleRadius);
  wall aWall(wallOrigin,wallVector);
  float circleWallCollisionTime = circleWallCollision(aCircle,aWall);
  cout << "Collision time: " << circleWallCollisionTime << "\n";

  assert(std::abs(circleWallCollisionTime - 0.658579) < 1e-6);

  cout << "\n***Moving Point and Stationary Circle***\n\n";

  vf pointPosition = {30,6}; vf pointVector = {-78,6};

  cout << "Point position: (" << pointPosition[0] << "," << pointPosition[1] << ")\n";
  cout << "Point vector: (" << pointVector[0] << "," << pointVector[1] << ")\n";

  circle stationaryCircle(circleCenter,{0,0},circleRadius);
  point aPoint(pointPosition,pointVector);

  float pointCircleCollisionTime = pointCircleCollision(aPoint,stationaryCircle);

  cout << "Collision time: " << pointCircleCollisionTime << "\n\n";

  assert(std::abs(pointCircleCollisionTime - 0.304855) < 1e-6);

  std::cout << "Part 2 - Chapter 8 - Collisions\n";

}
