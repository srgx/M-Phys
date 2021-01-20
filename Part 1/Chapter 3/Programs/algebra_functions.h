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

int findLastParenIndex(const std::string & str, int index);

std::string substituteX(const std::string & str, int valX);
std::string substituteNoX(const std::string & str);
std::string substituteParens(const std::string & str);

std::string addSub(const std::string & str);
std::string mulDiv(const std::string & str);
std::pair<std::string,int> onlyMulDiv(const std::string & str,int index);

std::string expo(const std::string & str);
std::string onlyExpo(const std::string & str);

std::string groupTerms(const std::string & str);

int countX(const std::string & str);
int countNums(const std::string & str);

#endif
