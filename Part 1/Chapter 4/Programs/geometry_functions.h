#ifndef GEOMETRY_FUNCTIONS__H__
#define GEOMETRY_FUNCTIONS__H__

#include <array>

typedef std::pair<float,float> point;
typedef std::array<point,3> triangle;
typedef std::pair<float,float> mvector;

// 3 sides. 3 angles, -1 means no info
typedef std::array<float,6> triangleInfo;

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
void showTriangle(const triangle & vertices);

triangleInfo solveTriangle(const triangleInfo & data);
int countSides(const triangleInfo & data);
int countAngles(const triangleInfo & data);
int countData(const triangleInfo & data,int from);
float cosineR(float a, float b, float c);
bool compareAprox(const triangleInfo & a, const triangleInfo & b);
bool hasAngleBetween(const triangleInfo & data);
bool isRightAngled(const triangleInfo & data);
float calcSide(float b, float c, float alfa);
float pythagore(float side, float hypotenuse);

triangleInfo solve3Sides(triangleInfo data);
triangleInfo solve2Angles1Side(triangleInfo data,int angles);
triangleInfo angleBetween2Sides(triangleInfo data);
triangleInfo rightAngle2Sides(triangleInfo data);
void thirdAngle(triangleInfo & data);

#endif
