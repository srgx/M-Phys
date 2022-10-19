#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>
#include "../Programs/numbers_functions.h"

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

  // -9.75
  iefloat arr12diff
    { 1,
      1, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  // -59.7
  iefloat arr14sum
    { 1,
      1, 0, 0, 0, 0, 1, 0, 0,
      1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1 };

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


  // 412515.5
  iefloat largeFloat
    { 0,
      1, 0, 0, 1, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 };


  // 51564.4375
  iefloat largeProduct
    { 0,
      1, 0, 0, 0, 1, 1, 1, 0,
      1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 };


  // 412535.75
  iefloat largeSum
    { 0,
      1, 0, 0, 1, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0 };


  // -----------------------------------------------------------------------

  // Addition

  // First Positive

    // 35.75 + 20.5 = 56.25
    iefloat sum = addFloats(first,second);
    assert(sum == firstSecondSum);
    assert(sum == addFloats(second,first));

    // 10.5 + 20.25 = 30.75
    sum = addFloats(arr1,arr2);
    assert(sum == arr12sum);

    // 10.5 + (-20.25) = -9.75
    sum = addFloats(arr1,negateFloat(arr2));
    assert(sum == arr12diff);

    // 10.5 + 0 = 10.5
    sum = addFloats(arr1,arr5);
    assert(sum == arr1);

    // 20.25 + (-10.5) = 9.75
    sum = addFloats(arr2,negateFloat(arr1));
    assert(sum == negateFloat(arr12diff));

    // 20.25 + 412515.5 = 412535.75
    sum = addFloats(arr2,largeFloat);
    assert(sum == largeSum);

  // First Negative

    // (-10.5) + 20.25 = 9.75
    sum = addFloats(negateFloat(arr1),arr2);
    assert(sum == negateFloat(arr12diff));

    // (-20.25) + 10.5 = (-9.75)
    sum = addFloats(negateFloat(arr2),arr1);
    assert(sum == arr12diff);

    // (-10.5) + 0 = (-10.5)
    sum = addFloats(negateFloat(arr1),arr5);
    assert(sum == negateFloat(arr1));

    // (-20.25) + (-412515.5) = (-412535.75)
    sum = addFloats(negateFloat(arr2),negateFloat(largeFloat));
    assert(sum == negateFloat(largeSum));


  // First Zero

    // 0 + 10.5 = 10.5
    sum = addFloats(arr5,arr1);
    assert(sum == arr1);

    // 0 + (-10.5) = (-10.5)
    sum = addFloats(arr5,negateFloat(arr1));
    assert(sum == negateFloat(arr1));

    // 0 + 0 = 0
    sum = addFloats(arr5,arr5);
    assert(sum == arr5);


  // Subtraction

  // First Positive

    // 56.25 - 20.5 = 35.75
    iefloat diff = subFloats(firstSecondSum,second);
    assert(diff==first);

    // 56.25 - 35.75 = 20.5
    diff = subFloats(firstSecondSum,first);
    assert(diff == second);

    // 10.5 - 20.25 = (-9.75)
    diff = subFloats(arr1,arr2);
    assert(diff == arr12diff);

    // 10.5 - (-20.25) = 30.75
    diff = subFloats(arr1,negateFloat(arr2));
    assert(diff == arr12sum);

    // 10.5 - 10.5 = 0
    diff = subFloats(arr1,arr1);
    assert(diff == arr5);

    // 10.5 - 0 = 10.5
    diff = subFloats(arr1,arr5);
    assert(diff == arr1);

  // First Negative

    // (-70.2) - (-70.2) = 0
    diff = subFloats(arr4,arr4);
    assert(diff == arr5);

    // (-10.5) - 20.25 = -30.75
    diff = subFloats(negateFloat(arr1),arr2);
    assert(diff == negateFloat(arr12sum));

    // (-10.5) - (-20.25) = 30.75
    diff = subFloats(negateFloat(arr1),negateFloat(arr2));
    assert(diff == negateFloat(arr12diff));

    // (-10.5) - 0 = (-10.5)
    diff = subFloats(negateFloat(arr1),arr5);
    assert(diff == negateFloat(arr1));

  // First Zero

    // 0 - 10.5 = (-10.5)
    diff = subFloats(arr5,arr1);
    assert(diff == negateFloat(arr1));

    // 0 - (-10.5) = 10.5
    diff = subFloats(arr5,negateFloat(arr1));
    assert(diff == arr1);

    // 0 - 0 = 0
    diff = subFloats(arr5,arr5);
    assert(diff == arr5);


  // Multiplication

  // First Positive

    // 35.75 * 20.5 = 732.875
    iefloat prod = mulFloats(first,second);
    assert(prod==firstSecondProd);

    // 20.5 * 35.75 = 732.875
    prod = mulFloats(second,first);
    assert(prod==firstSecondProd);

    // 10.5 * 20.25 = 212.625
    prod = mulFloats(arr1,arr2);
    assert(prod==arr12prod);

    // 20.25 * 10.5 = 212.625
    prod = mulFloats(arr2,arr1);
    assert(prod==arr12prod);

    // 20.25 * 0 = 0
    prod = mulFloats(arr2,arr5);
    assert(prod==arr5);

    // 10.5 * (-20.25) = -212.625
    prod = mulFloats(arr1,negateFloat(arr2));
    assert(prod==negateFloat(arr12prod));

    // 0.125 * 412515.5 = 51564.4375
    prod = mulFloats(arr3,largeFloat);
    assert(prod==largeProduct);

  // First Negative

    // (-10.5) * 20.25 = -212.625
    prod = mulFloats(negateFloat(arr1),arr2);
    assert(prod==negateFloat(arr12prod));

    // (-10.5) * (-20.25) = 212.625
    prod = mulFloats(negateFloat(arr1),negateFloat(arr2));
    assert(prod==arr12prod);

    // (-0.125) * 412515.5 = (-51564.4375)
    prod = mulFloats(negateFloat(arr3),largeFloat);
    assert(prod==negateFloat(largeProduct));

  // First Zero

    // 0 * 10.5 = 0
    prod = mulFloats(arr5,arr1);
    assert(prod==arr5);

    // 0 * (-10.5) = 0
    prod = mulFloats(arr5,negateFloat(arr1));
    assert(prod==arr5);

    // 0 * 0 = 0
    prod = mulFloats(arr5,arr5);
    assert(prod==arr5);

    // 0 * 412515.5 = 0
    prod = mulFloats(arr5,largeFloat);
    assert(prod==arr5);


  // Division

  // First Positive

    // 732.875 / 35.75 = 20.5
    iefloat quot = divFloats(firstSecondProd,first);
    assert(quot==second);

    // 732.875 / 20.5 = 35.75
    quot = divFloats(firstSecondProd,second);
    assert(quot==first);

    // 732.875 / 0 = 0
    quot = divFloats(firstSecondProd,arr5);
    assert(quot==arr5);

    // 51564.4375 / 412515.5 = 0.125
    quot = divFloats(largeProduct,largeFloat);
    assert(quot==arr3);

    // 51564.4375 / 0.125 = 412515.5
    quot = divFloats(largeProduct,arr3);
    assert(quot==largeFloat);

    // 51564.4375 / (-412515.5) = (-0.125)
    quot = divFloats(largeProduct,negateFloat(largeFloat));
    assert(quot==negateFloat(arr3));

  // First Negative

    // (-732.875) / 20.5 = (-35.75)
    quot = divFloats(negateFloat(firstSecondProd),second);
    assert(quot==negateFloat(first));

    // (-732.875) / 0 = 0
    quot = divFloats(negateFloat(firstSecondProd),arr5);
    assert(quot==arr5);

    // (-732.875) / (-20.5) = 35.75
    quot = divFloats(negateFloat(firstSecondProd),negateFloat(second));
    assert(quot==first);

    // (-51564.4375) / 412515.5 = (-0.125)
    quot = divFloats(negateFloat(largeProduct),largeFloat);
    assert(quot==negateFloat(arr3));


  // First Zero

    // 0 / 0 = 0
    quot = divFloats(arr5,arr5);
    assert(quot==arr5);

    // 0 / 20.5 = 0
    quot = divFloats(arr5,second);
    assert(quot==arr5);

    // 0 / (-20.5) = 0
    quot = divFloats(arr5,negateFloat(second));
    assert(quot==arr5);

    // 0 / 412515.5 = 0
    quot = divFloats(arr5,largeFloat);
    assert(quot==arr5);


  std::cout << "Part 1 - Chapter 1 - Exercise 2\n";

}
