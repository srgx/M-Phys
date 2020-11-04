#ifndef VECTORS_FUNCTIONS__H__
#define VECTORS_FUNCTIONS__H__
#include <vector>

std::vector<float> addVectors(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> subVectors(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> scaleVector(const std::vector<float> & vec, float scale);
float magnitude(const std::vector<float> & vec);
std::vector<float> norm(const std::vector<float> & vec);
float angleBetween(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> oppositeVector(const std::vector<float> & vec);

#endif
