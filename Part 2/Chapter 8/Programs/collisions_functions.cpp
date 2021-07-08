#include "collisions_functions.h"
#include <iostream>
#include <cmath>

using std::cout;

circle::circle(const vf & pos,
               const vf & dp,
               const float rad) : position(pos), displacement(dp), radius(rad){
}

wall::wall(const vf & pos,
           const vf & vec) : position(pos),vector(vec){
}

vf wall::normal() const{
  return {-vector[1],vector[0]};
}

point::point(const vf & pos,const vf & vec) : position(pos),vector(vec){
}

float intersectionTime(const vf & p1,const vf & v1,const vf & p2,const vf & v2){

  float sc1 = v2.at(0); float sc2 = v2.at(1);

  float det = v1.at(1) * sc1 - v1.at(0) * sc2;
  return det == 0 ?
    -1 :
    (sc1 * (p2.at(1) - p1.at(1)) -
     sc2 * (p2.at(0) - p1.at(0))) / det;

}

float circleWallCollision(const circle & cir,const wall & wal){

  // Wall normal (unit)
  vf n = wal.normal();
  float mag = sqrt(pow(n[0],2) + pow(n[1],2));
  n = mul(n,1/mag);

  // Vector from circle to wall start point
  vf a = sub(wal.position,cir.position);

  // Calculate dot product (a,n) to know
  // how far vector a goes in direction n
  float c = dot(a,n);

  // Circle is inside wall
  if (std::abs(c) < cir.radius){
    cout << "Embedded\n";
  } else {

    // How far is circle moving in direction n
    float v = dot(cir.displacement,n);

    if (v < 0) {
      cout << "None (v < 0)\n";
    } else {

      // Find radius vector perpendicular to wall
      vf r;
      if (c > 0){
        r = {n[0]*cir.radius,n[1]*cir.radius};
      } else {
        r = {n[0]*cir.radius*-1,n[1]*cir.radius*-1};
      }

      // Point of collision on circle circumference
      vf p = add(cir.position,r);

      float t = intersectionTime(p,cir.displacement,wal.position,wal.vector);

      // No collision in this time period
      if (t > 1){
        cout << "None (t > 1): " << t << std::endl;
      } else {
        return t;
      }

    }

  }

  return -1;

}

float pointCircleCollision(const point & pt, const circle & cir){

  vf w = {pt.position[0]-cir.position[0],pt.position[1]-cir.position[1]};
  float ww = dot(w,w);

  float cRadSq = pow(cir.radius,2);

  if (ww < cRadSq){
    cout << "Inside\n";
    return -1;
  }

  vf v = {pt.vector[0]-cir.displacement[0],pt.vector[1]-cir.displacement[1]};

  float a = dot(v,v);
  float b = dot(w,v);
  float c = ww - cRadSq;

  float root = pow(b,2) - a * c;

  if (root < 0) {
    cout << "None\n";
    return -1;
  }

  float t = (-b-sqrt(root))/a;
  if ((t > 1) || (t < 0)) {
    cout << "None\n";
    return -1;
  } else {
    return t;
  }

}

float circleCircleStraightCollision(const circle & cir1,float cir1speed,
                                    float cir1linearPosition,
                                    const circle & cir2,float cir2speed,
                                    float cir2linearPosition){

  float relSpeed = cir1speed - cir2speed;
  float d = cir1linearPosition - cir2linearPosition;
  float r = cir1.radius + cir2.radius;

  if(d < r){
    cout << "Embedded\n";
  } else {
    float t = (d - r) / relSpeed;
    if(t > 1 || t < 0){
      cout << "None\n";
    } else {
      return t;
    }
  }

  return -1;

}


float circleCircleCollision(const circle & cir1,const circle & cir2){

  vf w = sub(cir1.position,cir2.position);
  float r = cir1.radius + cir2.radius;
  float ww = dot(w,w);

  if (ww < pow(r,2)){
    cout << "Embedded\n";
  } else {
    vf v = sub(cir1.displacement,cir2.displacement);
    float a = dot(v,v);
    float b = dot(w,v);
    float c = ww - pow(r,2);
    float root = pow(b,2) - a * c;
    if(root < 0){
      cout << "None\n";
    } else {
      float t = (-b-sqrt(root))/a;
      if(t > 1 || t < 0){
        cout << "None\n";
      } else {
        return t;
      }
    }
  }

  return -1;

}

vf add(const vf & a,const vf & b){
  return {a[0]+b[0],a[1]+b[1]};
}

vf sub(const vf & a,const vf & b){
  return {a[0]-b[0],a[1]-b[1]};
}

vf mul(const vf & vec,float v){
  return {vec[0]*v,vec[1]*v};
}

float dot(const vf & a,const vf & b){
  return a[0]*b[0] + a[1]*b[1];
}
