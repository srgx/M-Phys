#include <iostream>
#include <array>
#include <cmath>

using std::array; using std::cout; using std::endl; using std::make_pair;
typedef std::pair<float,float> point;
typedef array<point,3> triangle;

void rotateFollow(const triangle & vertices,const point & target);
float calculateDistance(const point & a, const point & b);
point pointBetween(const point & a,const point & b, float distance);

// g++ ex2.cpp

int main(){

  triangle tr;
  tr.at(0) = make_pair(4,5);
  tr.at(1) = make_pair(20,25);
  tr.at(2) = make_pair(30,6);

  const point CENTER = make_pair(18,12);

  const point TARGET = make_pair(50,40);

  rotateFollow(tr,TARGET);

  //cout << calculateDistance(make_pair(4,3),make_pair(3,-2)) << endl;
}

point pointBetween(const point & a,const point & b, float distance){
  float totalDistance = calculateDistance(a,b);
  float ratio = distance / totalDistance;
  float x = a.first + ratio * (b.first - a.first);
  float y = a.second + ratio * (b.second - a.second);
  return make_pair(x,y);
}

float calculateDistance(const point & a, const point & b){
  return sqrt(pow(b.first-a.first,2) + pow(b.second-a.second,2));
}

void rotateFollow(const triangle & vertices,const point & target){

  // Find centrum of a triangle
  float x = (vertices.at(0).first + vertices.at(1).first + vertices.at(2).first) / 3;
  float y = (vertices.at(0).second + vertices.at(1).second + vertices.at(2).second) / 3;
  point center = make_pair(x,y);

  cout << "X: " << center.first << ", ";
  cout << "Y: " << center.second << endl;

  // Calculate distance from center to front vertex
  float centerToFrontLength = calculateDistance(center,vertices.at(0));

  // Calculate position of front vertex
  point newFrontPosition = pointBetween(center,target,centerToFrontLength);
  cout << newFrontPosition.first << ", " << newFrontPosition.second << endl;

  // Calculate rotation angle(angle between old front position, center and new front position)
  // ...

  // Rotate remaining 2 vertices and return new triangle
  // ...

}
