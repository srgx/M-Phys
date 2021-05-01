#ifndef GEOMETRY3D_FUNCTIONS__H__
#define GEOMETRY3D_FUNCTIONS__H__
#include <array>

typedef std::array<float,3> vector3d;
typedef std::array<float,2> vector2d;

float magnitude3d(const vector3d & v);
float dot3d(const vector3d & v1, const vector3d & v2);
vector3d unit3d(const vector3d & v);
vector3d crossProduct(const vector3d & v1, const vector3d & v2);
vector3d scale3d(const vector3d & v, float scale);
vector3d negate3d(const vector3d & v);
vector3d add3d(const vector3d & v1, const vector3d & v2);
vector3d sub3d(const vector3d & v1, const vector3d & v2);
float square(float x);

float linePlaneIntersection(const vector3d & linePt, const vector3d & lineVect,
                            const vector3d & planePt, const vector3d & planeNormal);

std::pair<float,vector3d> planePlaneIntersection
  (const vector3d & pt1, const vector3d & normal1,
   const vector3d & pt2, const vector3d & normal2);

vector2d pos3DToScreenPos(const vector3d & pt, const vector3d & observerPos,
                          const vector3d & observerVect, const vector3d & observerUp,
                          float fov,float h);

vector3d screenPosTo3DPos(const vector2d & viewportPos, const vector3d & observerVect,
                          const vector3d & observerUp, float fov, float h);



#endif
