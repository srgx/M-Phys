#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>
#include "../Programs/numbers_functions.h"

// g++ ex2.cpp ../Programs/numbers_functions.cpp

const int S = 32;

typedef std::array<int,S> iefloat;

int getExponentValue(const iefloat & arr);
vecin getRawExponent(const iefloat & arr);
vecin getMantissa(const iefloat & arr);
iefloat addFloats(const iefloat & first, const iefloat & second);

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

  iefloat first
    { 0,
      1, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  iefloat second
    { 0,
      1, 0, 0, 0, 0, 0, 1, 1,
      0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  iefloat firstSecondSum
    { 0,
      1, 0, 0, 0, 0, 1, 0, 0,
      1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  iefloat sum = addFloats(first,second);
  assert(sum == addFloats(second,first));
  assert(sum == firstSecondSum);

}

int getExponentValue(const iefloat & arr){
  return baseToValue(getRawExponent(arr),2) - 127;
}

vecin getRawExponent(const iefloat & arr){
  vecin e(8);
  for(int i=0;i<8;i++){ e.at(i) = arr.at(i+1); }
  return e;
}

vecin getMantissa(const iefloat & arr){

  int lastDigitIndex = arr.size()-1;
  while(lastDigitIndex>8 && arr.at(lastDigitIndex)==0){
    lastDigitIndex--;
  }

  vecin mantissa(lastDigitIndex - 7);

  // If exponent is not 0 leading 1 is implicit
  mantissa.at(0) = 1;
  for(int i=1;i<mantissa.size();i++){
    mantissa.at(i) = arr.at(i+8);
  }

  return mantissa;
}

iefloat addFloats(const iefloat & first, const iefloat & second){

  int firstExponent = getExponentValue(first);
  int secondExponent = getExponentValue(second);

  vecin exponent = getRawExponent(firstExponent>secondExponent ? first : second);
  assert(exponent.size() == 8);

  vecin firstMantissa = getMantissa(first);
  vecin secondMantissa = getMantissa(second);

  int diff = abs(firstExponent-secondExponent);

  // Shift to make exponents equal
  if(firstExponent>secondExponent){
    secondMantissa.insert(secondMantissa.end(),diff,0);
  }else if(firstExponent<secondExponent){
    firstMantissa.insert(firstMantissa.end(),diff,0);
  }

  vecin resultMantissa = addBinary(firstMantissa,secondMantissa);

  // Initialize vector with zeros
  vecin sum(S,0);

  // Set exponent
  std::copy(exponent.begin(),exponent.end(),sum.begin()+1);

  // Set mantissa
  std::copy(resultMantissa.begin()+1,resultMantissa.end(),sum.begin()+9);

  iefloat result;
  std::copy(sum.begin(),sum.end(),result.begin());

  return result;
}
