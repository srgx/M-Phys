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
float square(float x);
float degToRad(float deg);
float radToDeg(float rad);
float mytan2(float y,float x);

// g++ ex2.cpp

int main(){

  // triangle tr;
  // tr.at(0) = make_pair(-4,14);
  // tr.at(1) = make_pair(2,2);
  // tr.at(2) = make_pair(-10,2);
  //
  // point target = make_pair(20,6);
  //
  // triangle newTriangle = rotateFollow(tr,target);
  //
  // // (4,6)
  // assert(std::abs(newTriangle.at(0).first - 4)<1e-5);
  // assert(std::abs(newTriangle.at(0).second - 6)<1e-5);
  //
  // // (-8,12)
  // assert(std::abs(newTriangle.at(1).first - -8)<1e-5);
  // assert(std::abs(newTriangle.at(1).second - 0)<1e-5);


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

  // Rotate left
  result = rotatePoint(make_pair(-12,2),make_pair(-4,2),degToRad(90));
  assert(std::abs(result.first - -4)<1e-5);
  assert(std::abs(result.second - -6)<1e-5);

  // Rotate right
  result = rotatePoint(make_pair(-12,2),make_pair(-4,2),degToRad(-90));
  assert(std::abs(result.first - -4)<1e-5);
  assert(std::abs(result.second - 10)<1e-5);


  // point pnt = make_pair(2,2);
  // point around = make_pair(-4,6);
  // float angl = degToRad(90);
  // point newp = rotatePoint(pnt,around,angl);
  // cout << newp.first << ", " << newp.second << endl;

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
    return acos((square(m1)+square(m2)-square(m3))/(2*m1*m2));
  }

}

triangle rotateFollow(const triangle & vertices,const point & target){

  // Find centrum of a triangle
  const point centrum = triangleCenter(vertices);

  //cout << "Center: " << centrum.first << ", " << centrum.second << endl;

  mvector centerToFront = createVector(centrum,vertices.at(0));
  mvector centerToTarget = createVector(centrum,target);

  const float angle = calculateAngle(centerToFront,centerToTarget);

  //cout << "Angle: " << angle << endl;

  triangle result;
  for(int i=0;i<3;i++){
    //cout << "Stare: " << vertices.at(i).first << ", " << vertices.at(i).second << endl;
    result.at(i) = rotatePoint(vertices.at(i),centrum,angle);
    //cout << "Nowe: " << result.at(i).first << ", " << result.at(i).second << endl;
  }

  // cout << result.at(0).first << endl;
  // cout << result.at(0).second << endl;

  return result;

}

float magnitude(const mvector & vec){
  return sqrt(square(vec.first) + square(vec.second));
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

  const float atanVal = std::abs(atan2(tY,tX));

  float newX = sqrt(square(tX)+square(tY)) * cos(angle-atan2(tY,tX)) + s;
  float newY = sqrt(square(tX)+square(tY)) * sin(angle-atan2(tY,tX)) + t;

  return make_pair(newX,newY);

}

float square(float x){
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
    //return degToRad(deg);
    return deg * M_PI / 180;
  }
}
