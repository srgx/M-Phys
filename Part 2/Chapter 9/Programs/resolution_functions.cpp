#include "resolution_functions.h"
#include <cmath>
#include <array>

float dot(const vf & a,const vf & b){
  return a[0]*b[0] + a[1]*b[1];
}

float magn(const vf & vec){
  return sqrt(pow(vec[0],2) + pow(vec[1],2));
}

vf componentVector(const vf & vec,
                      const vf & dir){
  vf v = unit(dir);
  float comp = component(vec, dir);
  return {v[0] * comp,v[1]*comp};
}

float component(const vf & vec, const vf & directionVec){

  auto alpha = atan2(directionVec.at(1),directionVec.at(0));
  auto theta = atan2(vec.at(1),vec.at(0));

  auto mag = magn(vec);

  return mag*cos(theta-alpha);

}

vf unit(const vf & vec){
  float m = magn(vec);
  return {vec[0]/m,vec[1]/m};
}

vf resolveFixedCollision(const vf & velocity,const vf & n){
  vf c = componentVector(velocity,n);
  float val = {c[0] * 2};
  return {velocity[0]-val,velocity[1]-val};
}

std::array<vf,2> resolveCollisionFree1(float mass1, float mass2,
                                       float vel1, float vel2){

  return {{{2,3},{4,5}}};

}

