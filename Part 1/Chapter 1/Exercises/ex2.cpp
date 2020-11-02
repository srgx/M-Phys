#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>
#include "../Programs/numbers_functions.h"

// g++ ex2.cpp ../Programs/numbers_functions.cpp

int main(){


  // IEE float (32 bits)
  // sign - 1 bit, exponent - 8 bits, significand - 23 bits

  // 10.5 = 1010.1 = 1.0101e3
  // exponent = 3 + 127(bias) = 130
  // ignore first 1 in significand
  iefloat arr1
    { 0, // positive
      1, 0, 0, 0, 0, 0, 1, 0,
      0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // 20.25 = 10100.01 = 1.010001e4
  // exponent = 4 + 127(bias) = 131
  iefloat arr2
    { 0, // positive
      1, 0, 0, 0, 0, 0, 1, 1,
      0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // 0.125 = 0.001 = 1e-3
  // exponent = -3 + 127(bias) = 124
  iefloat arr3
    { 0, // positive
      0, 1, 1, 1, 1, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // -70.2 = 1000110.00110011001100... = 1.00011000110011001100...e6
  // exponent = 6 + 127(bias) = 133
  iefloat arr4
    { 1, // negative
      1, 0, 0, 0, 0, 1, 0, 1,
      0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0 };


  // 0.0 = 0.0 = 0.0e0
  // if exponent is zero leading 1 is not ignored
  iefloat arr5
    { 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // -----------------------------------------------------------------------

  // 35.75
  iefloat first
    { 0,
      1, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  // 20.5
  iefloat second
    { 0,
      1, 0, 0, 0, 0, 0, 1, 1,
      0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  // 56.25
  iefloat firstSecondSum
    { 0,
      1, 0, 0, 0, 0, 1, 0, 0,
      1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  // 732.875
  iefloat firstSecondProd
    { 0,
      1, 0, 0, 0, 1, 0, 0, 0,
      0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // 30.75
  iefloat arr12sum
    { 0,
      1, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  // -30.75
  iefloat minusArr12sum
    { 1,
      1, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  // 212.625
  iefloat arr12prod
    { 0,
      1, 0, 0, 0, 0, 1, 1, 0,
      1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // -----------------------------------------------------------------------

  // Addition

  iefloat sum = addFloats(first,second);
  assert(sum == firstSecondSum);
  assert(sum == addFloats(second,first));

  sum = addFloats(arr1,arr2);
  assert(sum == arr12sum);
  assert(sum == addFloats(arr2,arr1));

  // 0 Addition
  sum = addFloats(arr1,arr5);
  assert(sum == arr1);
  assert(sum == addFloats(arr5,arr1));

  // Subtraction

  iefloat diff = subFloats(firstSecondSum,second);
  assert(diff == first);

  diff = subFloats(firstSecondSum,first);
  assert(diff == second);

  // X - 0 Subtraction
  diff = subFloats(firstSecondSum,arr5);
  assert(diff == firstSecondSum);

  // 0 - X Subtraction
  diff = subFloats(arr5,arr12sum);
  assert(diff == minusArr12sum);

  // X - X Subtraction
  diff = subFloats(arr2,arr2);
  assert(diff == arr5);

  // Multiplication

  iefloat prod = mulFloats(first,second);
  assert(prod==firstSecondProd);

  prod = mulFloats(second,first);
  assert(prod==firstSecondProd);

  prod = mulFloats(arr2,arr1);
  assert(prod==arr12prod);

  prod = mulFloats(arr1,arr2);
  assert(prod==arr12prod);

  // 0 * X Multiplication
  prod = mulFloats(arr5,arr1);
  assert(prod==arr5);

  // X * 0 Multiplication
  prod = mulFloats(arr1,arr5);
  assert(prod==arr5);

  // Division

  // iefloat quot = divFloats(firstSecondProd,first);
  // // assert(quot==second);
  //
  // for(const auto & v : second){
  //   std::cout << v << "|";
  // }
  //
  // std::cout << std::endl;
  //
  // for(const auto & v : quot){
  //   std::cout << v << "|";
  // }
  //
  // std::cout << std::endl;


  std::cout << "Exit\n";
}
