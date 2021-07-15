#ifndef COLLISIONS_FUNCTIONS__H__
#define COLLISIONS_FUNCTIONS__H__
#include <array>

typedef std::array<float,2> vf;

class circle{
public:
  vf position;
  vf displacement;
  float radius;
  circle(const vf & pos, const vf & dp, const float rad);
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

float circleWallCollision(const circle & cir,const wall & wal);
float pointCircleCollision(const point & pt, const circle & cir);
float circleCircleStraightCollision(const circle & cir1,float cir1speed,
                                    float cir1linearPosition,
                                    const circle & cir2,float cir2speed,
                                    float cir2linearPosition);
float circleCircleCollision(const circle & cir1,const circle & cir2);
float circleCircleInnerCollision(const circle & cir1,const circle & cir2);

bool pointInsideRectangle(const vf & pt, const vf & rectCenter,
                          const vf & side1, const vf & side2);
bool pointOnRectangle(const vf & pt, const vf & rectCenter,
                      const vf & side1, const vf side2);

vf add(const vf & a,const vf & b);
vf sub(const vf & a,const vf & b);
vf mul(const vf & vec,float v);
vf unit(const vf & vec);
float dot(const vf & a,const vf & b);
float magn(const vf & vec);
float intersectionTime(const vf & p1,const vf & v1,const vf & p2,const vf & v2);
float component(const vf & vec, const vf & dir);



#endif
