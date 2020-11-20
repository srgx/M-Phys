#ifndef ALGEBRA_FUNCTIONS__H__
#define ALGEBRA_FUNCTIONS__H__
#include <vector>
#include <string>

typedef std::vector<float> vecflt;

struct compare{
  float key;
  compare(const float & i);
  bool operator()(const float & i);
};

struct eqResult{
  bool success;
  vecflt answer;
};

vecflt solveCubic(float a, float b, float c, float d);
eqResult solveSimultaneous(std::vector<vecflt> & equations);
int substitute(const std::string & str,int valX);
bool allDigits(const std::string & str);
std::string getSubexpFrom(const std::string & str,int index);
bool isExp(const std::string & str);
bool isParExp(const std::string & str);

#endif
