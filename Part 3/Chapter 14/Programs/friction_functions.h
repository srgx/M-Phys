#ifndef FRICTION_FUNCTIONS__H__
#define FRICTION_FUNCTIONS__H__
#include <array>

using std::array;

array<float,2> resultantForceOnObject(array<float,2> nonFrictionalForce,
                                      array<float,2> velocity,
                                      float coefficient);
float magnitude(array<float,2> vec);
array<float,2> unitVector(array<float,2> vec);
float component(array<float,2> vec,array<float,2> normVec);

#endif
