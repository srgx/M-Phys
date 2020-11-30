#include "geometry_functions.h"
#include <cmath>
#include <iostream>

using std::cout; using std::endl;

point pointBetween(const point & a,const point & b, float distance){
  float totalDistance = calculateDistance(a,b);
  float ratio = distance / totalDistance;
  float x = a.first + ratio * (b.first - a.first);
  float y = a.second + ratio * (b.second - a.second);
  return std::make_pair(x,y);
}

float calculateDistance(const point & a, const point & b){
  return magnitude(createVector(a,b));
}

// Angle between vectors
float calculateAngle(const mvector & a, const mvector & b){

  mvector c = std::make_pair(b.first-a.first,b.second-a.second);
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
  return std::make_pair(b.first-a.first,b.second-a.second);
}

point triangleCenter(const triangle & vertices){
  float x = (vertices.at(0).first + vertices.at(1).first + vertices.at(2).first) / 3;
  float y = (vertices.at(0).second + vertices.at(1).second + vertices.at(2).second) / 3;
  return std::make_pair(x,y);
}

point rotatePoint(const point & pnt, const point & around, float angle){

  float x = pnt.first; float y = pnt.second;
  float s = around.first; float t = around.second;
  float tX = x - s; float tY = y - t; // Translate point

  float newX = sqrt(sqr(tX)+sqr(tY)) * cos(-angle-atan2(tY,tX)) + s;
  float newY = sqrt(sqr(tX)+sqr(tY)) * sin(angle-atan2(tY,tX)) + t;

  return std::make_pair(newX,newY);

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

triangleInfo solveTriangle(const triangleInfo & data){

  int sides = countSides(data); int angles = countAngles(data);

  // 3 sides
  if(3==sides){

    // cout << "FIRST\n";

    int a = data.at(0); int b = data.at(1); int c = data.at(2);
    triangleInfo result = data;

    // Calculate angles with cosine rule
    result.at(3) = radToDeg(cosineR(a,b,c));
    result.at(4) = radToDeg(cosineR(b,c,a));
    result.at(5) = radToDeg(cosineR(c,a,b));

    return result;

  // 2 angles and 1 side
  }else if(sides>=1&&angles>=2){

    // cout << "SECOND\n";

    triangleInfo result = data;

    // find 3rd angle
    if(2==angles){
      float sum = 0;

      // sum of 2 angles
      for(int i=3;i<6;i++){
        if(result.at(i)>=0){ sum += result.at(i); }
      }

      // calculate and set 3rd angle
      for(int i=3;i<6;i++){
        if(result.at(i)<0){ result.at(i) = 180 - sum; break; }
      }

    }

    // 3 angles and at least 1 side are now known

    // Find index of known side
    int sideIndex = 0;
    while(result.at(sideIndex)<0){ sideIndex++; }

    // Calculate proportion. Add 3 to sideIndex to find corresponding angle
    const float proportion =
      result.at(sideIndex) / sin(degToRad(result.at(sideIndex+3)));

    // Calculate remaining sides from sine rule
    // a = sin(alfa) * (c/sin(gamma))
    for(int i=0;i<3;i++){
      if(i!=sideIndex){
        result.at(i) =
          sin(degToRad(result.at(i+3))) * proportion;
      }
    }

    return result;

  // 2 sides and angle between them
  }else if(hasAngleBetween(data)){
    int angleIndex = 3;


    while(data.at(angleIndex)==-1){ angleIndex++; }

    // a^2 = b^2 + c^2 - 2bc * cos(alfa)

    // alfa is angle between b and c

    // from cosine rule
    // length of 3rd side is sqrt(b^2 + c^2 - 2bc * cos(alfa))

    // 3 sides are now known etc

    switch(angleIndex){
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
    }
  }else if(isRightAngled){
    //
  }

}

int countData(const triangleInfo & data, int from){
  int count = 0; int end = from + 3; // read 3 elements
  for(int i=from;i<end;i++){
    if(data.at(i)>=0){ count++; }
  }
  return count;
}

int countSides(const triangleInfo & data){
  return countData(data,0);
}

int countAngles(const triangleInfo & data){
  return countData(data,3);
}

float cosineR(float a, float b, float c){
  return acos((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
}

bool compareAprox(const triangleInfo & a, const triangleInfo & b){
  for(int i=0;i<a.size();i++){
    if(std::abs(a.at(i)-b.at(i))>0.9){
      return false;
    }
  }
  return true;
}

bool hasAngleBetween(const triangleInfo & data){
  float a = data.at(0); float b = data.at(1); float c = data.at(2);
  float d = data.at(3); float e = data.at(4); float f = data.at(5);
  return (a!=-1&&b!=-1&&f!=-1)||
         (b!=-1&&c!=-1&&d!=-1)||
         (c!=-1&&a!=-1&&e!=-1);
}

bool isRightAngled(const triangleInfo & data){
  return true;
}
