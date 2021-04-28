#include <iostream>
#include <cmath>
#include "geometry3d_functions.h"


float magnitude3d(const vector3d & v){
  return sqrt(pow(v[0],2) + pow(v[1],2) + pow(v[2],2));
}

float dot3d(const vector3d & v1, const vector3d & v2){
  return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

std::array<float,3> unit3d(const vector3d & v){
  float m = magnitude3d(v);
  return {v[0]/m, v[1]/m, v[2]/m};
}

vector3d crossProduct(const vector3d & v1, const vector3d & v2){
  return { v1[1] * v2[2] - v2[1] * v1[2],
           v1[2] * v2[0] - v1[0] * v2[2],
           v1[0] * v2[1] - v1[1] * v2[0] };
}

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


