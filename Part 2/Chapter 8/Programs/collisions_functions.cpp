#include "collisions_functions.h"
#include <iostream>
#include <cmath>

using std::cout;

circle::circle(const vf & pos,
               const vf & dp,
               const float rad) : position(pos), displacement(dp), radius(rad){
}

straightCircle::straightCircle(const float & pos, const float & rad, const float spd) :
                               position(pos), radius(rad), speed(spd){
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
  vf n = unit(wal.normal());

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
      vf r = mul(n,cir.radius - (c > 0 ? 0 : -1));

      // Point of collision on circle circumference
      vf p = add(cir.position,r);

      float t = intersectionTime(p,cir.displacement,wal.position,wal.vector);

      // No collision in this time period
      if (t > 1){
        cout << "None (t > 1): " << t << '\n';
      } else {
        return t;
      }

    }

  }

  return -1;

}

float pointCircleCollision(const point & pt, const circle & cir){

  vf w = sub(pt.position,cir.position);
  float ww = dot(w,w);
  float cRadSq = pow(cir.radius,2);

  if (ww < cRadSq){
    cout << "Inside\n";
  } else {

    vf v = sub(pt.vector,cir.displacement);
    float a = dot(v,v); float b = dot(w,v);
    float root = pow(b,2) - a * (ww - cRadSq);

    if (root < 0) {
      cout << "None\n";
    } else {

      float t = (-b - sqrt(root)) / a;

      if ((t > 1) || (t < 0)) {
        cout << "None\n";
      } else {
        return t;
      }

    }
  }

  return -1;

}

float circleCircleStraightCollision(const straightCircle & cir1,
                                    const straightCircle & cir2){

  float relSpeed = cir1.speed - cir2.speed;
  float d = std::abs(cir1.position - cir2.position);
  float twoR = cir1.radius + cir2.radius;

  if(d < twoR){
    cout << "Embedded\n";
  } else {
    float t = (d - twoR) / relSpeed;
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
      float t = (-b - sqrt(root))/a;
      if(t > 1 || t < 0){
        cout << "None\n";
      } else {
        return t;
      }
    }
  }

  return -1;

}

float circleCircleInnerCollision(const circle & cir1,const circle & cir2){

  vf w = sub(cir1.position,cir2.position);
  float r = cir2.radius - cir1.radius;
  float ww = dot(w,w);

  if (ww > pow(r,2)){
    cout << ((ww < pow(cir2.radius+cir2.radius,2)) ? "Embedded\n" : "Outside\n");
  } else {
    vf v = sub(cir1.displacement,cir2.displacement);
    float a = dot(v,v); float b = dot(w,v);
    float t = (-b + sqrt(pow(b,2) - a * (ww - pow(r,2)))) / a;
    if (t > 1) {
      cout << "None\n";
    } else {
      return t;
    }
  }

  return -1;

}

bool pointInsideRectangle(const vf & pt, const vf & rectCenter,
                          const vf & side1, const vf & side2){

  vf vect = sub(pt,rectCenter);
  return !(std::abs(component(vect,side1)) > magn(side1) ||
           std::abs(component(vect,side2)) > magn(side2));

}

bool pointOnRectangle(const vf & pt, const vf & rectCenter,
                      const vf & side1, const vf side2){

  const float d = 1e-3;
  const vf vect = sub(pt,rectCenter);
  const float s1 = magn(side1); const float s2 = magn(side2);

  return std::abs(std::abs(dot(vect,mul(side1,1/s1))) - s1) < d ||
         std::abs(std::abs(dot(vect,mul(side2,1/s2))) - s2) < d;

}

float magn(const vf & vec){
  return sqrt(pow(vec[0],2) + pow(vec[1],2));
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

vf unit(const vf & vec){
  float m = magn(vec);
  return {vec[0]/m,vec[1]/m};
}

float component(const vf & vec, const vf & dir){
  return dot(vec,unit(dir));
}
