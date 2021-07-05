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

  float tc1 = v1.at(0);
  float tc2 = v1.at(1);

  float sc1 = v2.at(0);
  float sc2 = v2.at(1);

  float det = tc2*sc1-tc1*sc2;

  if(det==0){
    return 0;
  } else {
    float con1 = p2.at(0)-p1.at(0);
    float con2 = p2.at(1)-p1.at(1);
    return (sc1*con2-sc2*con1)/det;
  }

}

float circleWallCollision(const circle & cir,const wall & wal){

  // Wall normal
  vf n = wal.normal();
  float mag = sqrt(pow(n[0],2)+pow(n[1],2));
  n = {n[0]/mag,n[1]/mag};

  // Vector from circle to wall start point
  vf a = {wal.position[0]-cir.position[0],wal.position[1]-cir.position[1]};

  // Calculate dot product (a,n) to know how
  // far vector a goes in direction n
  float c = a[0]*n[0] + a[1]*n[1];

  // Circle is inside wall
  if (std::abs(c) < cir.radius){
    cout << "Embedded\n";
    return -1;
  }

  // Find radius vector perpendicular to wall
  vf r;
  if (c < 0){
    r = {n[0]*cir.radius,n[1]*cir.radius};
  } else {
    r = {n[0]*cir.radius*-1,n[1]*cir.radius*-1};
  }

  // How far is circle moving in direction n
  float v = cir.displacement[0]*n[0]+cir.displacement[1]*n[1];

  if (v < 0) {
    cout << "None (v < 0)\n";
    return -1;
  }

  vf p = {cir.position[0]+r[0],cir.position[1]+r[1]};

  float t = intersectionTime(p,
                             cir.displacement,
                             wal.position,
                             wal.vector);


  if (t > 1){
    cout << "None (t > 1): " << t << std::endl;
    return -1;
  } else {
    return t;
  }

}

float pointCircleCollision(const point & pt, const circle & cir){

  vf w = {pt.position[0]-cir.position[0],pt.position[1]-cir.position[1]};
  float ww = w[0]*w[0] + w[1]*w[1];

  float cRadSq = pow(cir.radius,2);

  if (ww < cRadSq){
    cout << "Inside\n";
    return -1;
  }

  vf v = {pt.vector[0]-cir.displacement[0],pt.vector[1]-cir.displacement[1]};

  float a = v[0]*v[0]+v[1]*v[1];
  float b = w[0]*v[0]+w[1]*v[1];
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

vf sub(const vf & a,const vf & b){
  return {a[0]-b[0],a[1]-b[1]};
}
