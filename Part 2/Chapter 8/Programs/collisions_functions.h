#ifndef COLLISIONS_FUNCTIONS__H__
#define COLLISIONS_FUNCTIONS__H__
#include <array>
#include <vector>

typedef std::array<float,2> vf;

class circle{
public:
  vf position;
  vf displacement;
  float radius;
  circle(const vf & pos, const vf & dp, const float rad);
};

class straightCircle{
public:
  float position;
  float radius;
  float speed;
  straightCircle(const float & pos, const float & rad, const float spd);
};

class wall{
public:
  vf position;
  vf vector;
  wall(const vf & pos,const vf & vec);
  vf normal() const;
};

class point{
public:
  vf position;
  vf vector;
  point(const vf & position,const vf & vector);
};

class rectangle{
public:
  vf position;
  vf side1;
  vf side2;
  rectangle(const vf & pos, const vf & s1, const vf & s2);
};

float circleWallCollision(const circle & cir,const wall & wal);
float pointCircleCollision(const point & pt, const circle & cir);
float circleCircleStraightCollision(const straightCircle & cir1,
                                    const straightCircle & cir2);
float circleCircleCollision(const circle & cir1,const circle & cir2);
float circleCircleInnerCollision(const circle & cir1,const circle & cir2);

bool pointInsideRectangle(const vf & pt, const vf & rectCenter,
                          const vf & side1, const vf & side2);
bool pointOnRectangle(const vf & pt, const vf & rectCenter,
                      const vf & side1, const vf side2);
float pointRectangleIntersection(const point & pt, const rectangle & rec);
float rectangleRectangleCollisionStraight(const rectangle & rec1,const rectangle & rec2);
float rrVertexCollisionStraight(const rectangle & rec1,const rectangle & rec2);
std::vector<vf> pointsToCheck(const vf & r1, const vf & r2, const vf & displacement);

std::vector<vf> drawEllipseByFoci(const vf & focus1, const vf & focus2,
                                  float diameter,int resolution);


float angleBetween(const vf & v1, const vf & v2);

vf add(const vf & a,const vf & b);
vf sub(const vf & a,const vf & b);
vf mul(const vf & vec,float v);
vf unit(const vf & vec);
vf normal(const vf & vec);
vf negate(const vf & vec);
vf rotateVector(vf v, float alpha);
std::vector<vf> drawEllipseByAxes(const vf & center, float a, float b, float alpha);

float min(float a, float b);
float dot(const vf & a,const vf & b);
float magn(const vf & vec);
float intersectionTime(const vf & p1,const vf & v1,const vf & p2,const vf & v2);
float component(const vf & vec, const vf & dir);



#endif
