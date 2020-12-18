#ifndef VECTORS_FUNCTIONS__H__
#define VECTORS_FUNCTIONS__H__
#include <vector>
#include <array>

std::vector<float> addVectors(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> subVectors(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> scaleVector(const std::vector<float> & vec, float scale);
float magnitude(const std::vector<float> & vec);
std::vector<float> norm(const std::vector<float> & vec);
std::vector<float> normalVector(const std::vector<float> & vec);
float angleBetween(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> oppositeVector(const std::vector<float> & vec);
float determinant(const std::vector<std::vector<float>> & array);

std::array<std::vector<float>,4> constructSquare(const std::vector<float> & a, const std::vector<float> & b);
std::array<std::vector<float>,3> constructEquilateralTriangle(const std::vector<float> & a, const std::vector<float> & b);
void createA(float legLength, float angleAtTop, float serifProp,
             float crossbarProp, float crossbarHeight, float serifAlign,
             float crossbarAlign);




#endif
