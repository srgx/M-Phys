#ifndef RESOLUTION_FUNCTIONS__H__
#define RESOLUTION_FUNCTIONS__H__
#include <array>

typedef std::array<float,2> vf;

float dot(const vf & a,const vf & b);
float magn(const vf & vec);
vf componentVector(const vf & vec, const vf & dir);
float component(const vf & vec, const vf & directionVec);
vf unit(const vf & vec);
vf resolveFixedCollision(const vf & velocity,const vf & n);

#endif
