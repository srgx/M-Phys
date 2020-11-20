#ifndef GEOMETRY_FUNCTIONS__H__
#define GEOMETRY_FUNCTIONS__H__

#include <array>

typedef std::pair<float,float> point;
typedef std::array<point,3> triangle;
typedef std::pair<float,float> mvector;

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

#endif
