#include <cassert>
#include "functions.h"
#include <iostream>

// g++ arithmetic.cpp functions.cpp

int main(){

  // Add fractions
  fraction fr = addFractions({ 4, 6 },{ 5, 14 });
  assert(fr.numerator == 86); assert(fr.denominator == 84);
  fr = addFractions({ 8, 33 },{ 9, 7 });
  assert(fr.numerator == 353); assert(fr.denominator == 231);

  // Generate prime numbers
  assert(listOfPrimes(100) ==
         std::vector<int> ({ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                             31, 37, 41, 43, 47, 53, 59, 61, 67,
                             71, 73, 79, 83, 89, 97 }));

}
