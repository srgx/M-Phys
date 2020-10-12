#ifndef ALGEBRA_FUNCTIONS__H__
#define ALGEBRA_FUNCTIONS__H__
#include <vector>

typedef std::vector<float> vecflt;

struct compare{
  float key;
  compare(const float & i);
  bool operator()(const float & i);
};

vecflt solveCubic(float a, float b, float c, float d);
vecflt solveSimultaneous(std::vector<vecflt> & equations);

#endif
