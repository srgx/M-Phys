#ifndef FUNCTIONS__H__
#define FUNCTIONS__H__

#include <vector>
#include <array>

using std::vector;
using std::array;

struct fraction{
  int numerator;
  int denominator;
};

struct rootres{
  float result;
  bool error;
};

fraction addFractions(fraction f1, fraction f2);
vector<int> listOfPrimes(int m);
vector<int> primeFactors(int n);
int gcd(int n, int m);
int lcm(int n, int m);
int strictModulo(int n, int m);
array<int,2> naiveClock(int oldHours, int oldMinutes, int addHours, int addMinutes);
array<int,2> cleverClock(int oldHours, int oldMinutes, int addHours, int addMinutes);
array<int,2> positionInGrid(int squareNumber, int numCols);
float monthlyPayment(float initialAmount,float annualInterest, int years);
float debtAfterMonths(float initialAmount, float annualInterest, float perMonth, float months);
rootres mthRoot(float n,float m);

#endif
