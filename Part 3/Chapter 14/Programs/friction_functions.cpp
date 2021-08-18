#include <iostream>
#include <cmath>
#include "friction_functions.h"

array<float,2> resultantForceOnObject(array<float,2> nonFrictionalForce,
                                      array<float,2> velocity,
                                      float coefficient){

  // Slope direction
  array<float,2> tang = unitVector(velocity);

  // Vector perpendicular to slope
  array<float,2> norm = {-tang[1],tang[0]};

  // Perpendicular force, W * cos(theta)
  float normalForce = component(nonFrictionalForce,norm);

  // Force parallel to slope, W * sin(theta)
  float tangentialForce = component(nonFrictionalForce,tang);

  // Friction, coefficient * W * cos(theta)
  float frictionalForce = coefficient * normalForce;

  float totalForce = tangentialForce - frictionalForce;

  // Return total force vector
  return frictionalForce > tangentialForce &&
         magnitude(velocity) > 0 ?
           array<float,2>({0,0}) :
           array<float,2>({tang[0] * totalForce,tang[1] * totalForce});

}

float magnitude(array<float,2> vec){
  return sqrt(pow(vec[0],2)+pow(vec[1],2));
}

array<float,2> unitVector(array<float,2> vec){
  float mag = magnitude(vec);
  return { vec[0]/mag, vec[1]/mag };
}

float component(array<float,2> vec,array<float,2> normVec){
  float alpha = atan2(normVec[1],normVec[0]);
  float theta = atan2(vec[1],vec[0]);
  return magnitude(vec) * cos(theta-alpha);
}
