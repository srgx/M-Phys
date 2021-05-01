#include <iostream>
#include <cmath>
#include "geometry3d_functions.h"


float magnitude3d(const vector3d & v){
  return sqrt(square(v[0]) + square(v[1]) + square(v[2]));
}

float dot3d(const vector3d & v1, const vector3d & v2){
  return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

std::array<float,3> unit3d(const vector3d & v){
  return scale3d(v,1/magnitude3d(v));
}

vector3d crossProduct(const vector3d & v1, const vector3d & v2){
  return { v1[1] * v2[2] - v2[1] * v1[2],
           v1[2] * v2[0] - v1[0] * v2[2],
           v1[0] * v2[1] - v1[1] * v2[0] };
}

vector3d scale3d(const vector3d & v, float scale){
  return { v[0] * scale, v[1] * scale, v[2] * scale };
}

vector3d negate3d(const vector3d & v){
  return { -v[0], -v[1], -v[2] };
}

vector3d add3d(const vector3d & v1, const vector3d & v2){
  return { v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2] };
}

vector3d sub3d(const vector3d & v1, const vector3d & v2){
  return(add3d(v1,negate3d(v2)));
}

float square(float x){ return pow(x,2); }

float linePlaneIntersection(const vector3d & linePt, const vector3d & lineVect,
                            const vector3d & planePt, const vector3d & planeNormal){

  float d = dot3d(lineVect,planeNormal);

  if (0 == d) {
    std::cout << "Really no intersection\n";
    return d;
  } else {

    vector3d v = { linePt[0] - planePt[0],
                   linePt[1] - planePt[1],
                   linePt[2] - planePt[2] };

    return dot3d(v,planeNormal)/d;

  }

}

std::pair<float,vector3d> planePlaneIntersection
  (const vector3d & pt1, const vector3d & normal1,
   const vector3d & pt2, const vector3d & normal2){

  vector3d v = crossProduct(normal1,normal2);
  vector3d u = crossProduct(normal1,v);
  float p = linePlaneIntersection(pt1,u,pt2,normal2);

  vector3d resultVector;
  if (0 == p) {
    std::cout << "No intersection\n";
    resultVector = vector3d({0,0,0});
  } else {
    resultVector = v;
  }

  return std::make_pair(p,resultVector);

}

vector2d pos3DToScreenPos(const vector3d & pt, const vector3d & observerPos,
                          const vector3d & observerVect, const vector3d & observerUp,
                          float fov,float h){

  vector3d observerRight = crossProduct(observerUp,observerVect);
  vector3d v = {pt[0] - observerPos[0], pt[1] - observerPos[1], pt[2] - observerPos[2]};
  float z = dot3d(v,observerVect);
  float d = h * tan(fov);
  float x = d * dot3d(v,observerRight) / z;
  float y = d * dot3d(v,observerUp) / z;

  return {x,-y};

}

vector3d screenPosTo3DPos(const vector2d & viewportPos, const vector3d & observerVect,
                          const vector3d & observerUp, float fov, float h){

  vector3d observerRight = crossProduct(observerUp,observerVect);
  float d = h / tan(fov);

  vector3d obsV = scale3d(observerVect,d);
  vector3d obsU = scale3d(observerUp,viewportPos[1]);
  vector3d obsP = scale3d(observerRight,viewportPos[0]);

  return add3d(sub3d(obsV,obsU),obsP);

}

