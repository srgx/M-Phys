#ifndef FUNCTIONS__H__
#define FUNCTIONS__H__

#include <vector>

struct fraction{
  int numerator;
  int denominator;
};

fraction addFractions(fraction f1, fraction f2);
std::vector<int> listOfPrimes(int m);

#endif
