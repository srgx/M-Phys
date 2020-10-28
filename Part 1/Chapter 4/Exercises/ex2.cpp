#include <iostream>
#include <array>
#include <cmath>
#include <cassert>

using std::array; using std::cout; using std::endl; using std::make_pair;
typedef std::pair<float,float> point;
typedef std::pair<float,float> mvector;
typedef array<point,3> triangle;

triangle rotateFollow(const triangle & vertices,const point & target);
float calculateDistance(const point & a, const point & b);
point pointBetween(const point & a,const point & b, float distance);
float calculateAngle(const mvector & a, const mvector & b);
float magnitude(const mvector & vec);
mvector createVector(const point & a, const point & b);
point triangleCenter(const triangle & vertices);
point rotatePoint(const point & pnt, const point & around, float angle);
float sqr(float x);
float degToRad(float deg);
float radToDeg(float rad);
float mytan2(float y,float x);

// g++ ex2.cpp

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

point pointBetween(const point & a,const point & b, float distance){
  float totalDistance = calculateDistance(a,b);
  float ratio = distance / totalDistance;
  float x = a.first + ratio * (b.first - a.first);
  float y = a.second + ratio * (b.second - a.second);
  return make_pair(x,y);
}

float calculateDistance(const point & a, const point & b){
  return magnitude(createVector(a,b));
}

// Angle between vectors
float calculateAngle(const mvector & a, const mvector & b){

  mvector c = make_pair(b.first-a.first,b.second-a.second);
  float m1 = magnitude(a); float m2 = magnitude(b); float m3 = magnitude(c);

  // Error(if m1 or m2 == 0) or vectors are equal
  if(m1==0||m2==0||m3==0){
    return 0;
  }else{
    return acos((sqr(m1)+sqr(m2)-sqr(m3))/(2*m1*m2));
  }

}

triangle rotateFollow(const triangle & vertices,const point & target){

  // Find centrum of a triangle
  const point centrum = triangleCenter(vertices);

  mvector centerToFront = createVector(centrum,vertices.at(0));
  mvector centerToTarget = createVector(centrum,target);

  const float angle = calculateAngle(centerToFront,centerToTarget);

  triangle result;
  for(int i=0;i<3;i++){
    result.at(i) = rotatePoint(vertices.at(i),centrum,-angle);
  }

  return result;

}

float magnitude(const mvector & vec){
  return sqrt(sqr(vec.first) + sqr(vec.second));
}

mvector createVector(const point & a, const point & b){
  return make_pair(b.first-a.first,b.second-a.second);
}

point triangleCenter(const triangle & vertices){
  float x = (vertices.at(0).first + vertices.at(1).first + vertices.at(2).first) / 3;
  float y = (vertices.at(0).second + vertices.at(1).second + vertices.at(2).second) / 3;
  return make_pair(x,y);
}

point rotatePoint(const point & pnt, const point & around, float angle){

  float x = pnt.first; float y = pnt.second;
  float s = around.first; float t = around.second;
  float tX = x - s; float tY = y - t; // Translate point

  float newX = sqrt(sqr(tX)+sqr(tY)) * cos(-angle-atan2(tY,tX)) + s;
  float newY = sqrt(sqr(tX)+sqr(tY)) * sin(angle-atan2(tY,tX)) + t;

  return make_pair(newX,newY);

}

float sqr(float x){
  return pow(x,2);
}

float degToRad(float deg){
  return deg * 0.0174532925;
}

float radToDeg(float rad){
  return rad * 57.2957795;
}

float mytan2(float y,float x){
  float deg = 1;
  if(x==0&&y<0){
    deg = 90;
  }else if(x==0&&y>=0){
    deg = -90;
  }else if(y==0&&x<0){
    deg = 0;
  }else if(y==0&&x>=0){
    deg = -180;
  }else if(deg==1){
    return atan(y/x);
  }else{
    return degToRad(deg);
  }
}
