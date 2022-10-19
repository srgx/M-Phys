#include <iostream>
#include <cassert>
#include <cmath>
#include "arithmetic_functions.h"

using std::vector;
using std::array;

int main(){

  // Add fractions
  fraction fr = addFractions({ 4, 6 },{ 5, 14 });
  assert(fr.numerator == 86); assert(fr.denominator == 84);
  fr = addFractions({ 8, 33 },{ 9, 7 });
  assert(fr.numerator == 353); assert(fr.denominator == 231);
  fr = addFractions({ 17, 4 },{ 8, 2 });
  assert(fr.numerator == 66); assert(fr.denominator == 8);

  // Generate prime numbers
  assert(listOfPrimes(100) ==
              vector<int> ({ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                             31, 37, 41, 43, 47, 53, 59, 61, 67,
                             71, 73, 79, 83, 89, 97 }));

  // Find prime factors
  assert(primeFactors(228) == vector<int>({ 2, 2, 3, 19 }));
  assert(primeFactors(189) == vector<int>({ 3, 3, 3, 7 }));
  assert(primeFactors(300) == vector<int>({ 2, 2, 3, 5, 5 }));

  // Greatest Common Divisor
  assert(gcd(60,24) == 12);
  assert(gcd(779,123) == 41);
  assert(gcd(6000,2500) == 500);

  // Least Common Multiple
  assert(lcm(10,75) == 150);
  assert(lcm(24,38) == 456);
  assert(lcm(512,360) == 23040);

  // Modulo
  assert(15%5==0);
  assert(-11%5==-1);
  assert(-3%5==-3);

  // Strict Modulo
  assert(strictModulo(15,5)==0);
  assert(strictModulo(-11,5)==4);
  assert(strictModulo(-3,5)==2);


  const array<array<int,2>,4> times = {{{ 2, 5 }, { 6, 35 }, { 4, 45 }, { 12, 10 }}};

  // Naive Clock
  assert(naiveClock(11,45,2,20) == times.at(0));
  assert(naiveClock(5,15,1,20) == times.at(1));
  assert(naiveClock(4,30,12,15) == times.at(2));
  assert(naiveClock(12,5,12,5) == times.at(3));

  // Clever Clock
  assert(cleverClock(11,45,2,20) == times.at(0));
  assert(cleverClock(5,15,1,20) == times.at(1));
  assert(cleverClock(4,30,12,15) == times.at(2));
  assert(cleverClock(12,5,12,5) == times.at(3));


  const array<array<int,2>,3> positions = {{{ 0, 0 }, { 1, 2 }, { 2, 3 }}};

  // Position In Grid
  assert(positionInGrid(0,4) == positions.at(0));
  assert(positionInGrid(6,4) == positions.at(1));
  assert(positionInGrid(11,4) == positions.at(2));

  const float MONTHLY = 1060.66;
  const float AMOUNT = 1e5;
  const float INTEREST = 5;

  // Debts
  assert(std::abs(monthlyPayment(AMOUNT,INTEREST,10) - MONTHLY)<0.01);
  assert(debtAfterMonths(AMOUNT,INTEREST,MONTHLY,0)>0);
  assert(debtAfterMonths(AMOUNT,INTEREST,MONTHLY,50)>0);
  assert(debtAfterMonths(AMOUNT,INTEREST,MONTHLY,119)>0);
  assert(debtAfterMonths(AMOUNT,INTEREST,MONTHLY,120)<=0);

  // Root
  assert(mthRoot(16,2).result == 4);
  assert(mthRoot(-16,2).error);
  assert(mthRoot(25,2).result == 5);
  assert(mthRoot(-125,3).result == -5);
  assert(mthRoot(-4096,4).error);
  assert(mthRoot(4096,4).result == 8);
  assert(mthRoot(-16807,5).result == -7);

  std::cout << "Part 1 - Chapter 2 - Arithmetic\n";

}
