#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>
#include "../Programs/functions.h"

// g++ ex2.cpp ../Programs/functions.cpp

using std::array;

const int S = 32;

int getExponentValue(const array<int,S> & arr);
vecstr getRawExponent(const array<int,S> & arr);
vecstr getMantissa(const array<int,S> & arr);
array<int,S> addFloats(const array<int,S> & first, const array<int,S> & second);

int main(){


  // IEE float (32 bits)
  // sign - 1 bit, exponent - 8 bits, significand - 23 bits

  // 10.5 = 1010.1 = 1.0101e3
  // exponent = 3 + 127(bias) = 130
  // ignore first 1 in significand
  array<int,S> arr1
    { 0, // positive
      1, 0, 0, 0, 0, 0, 1, 0,
      0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // 20.25 = 10100.01 = 1.010001e4
  // exponent = 4 + 127(bias) = 131
  array<int,S> arr2
    { 0, // positive
      1, 0, 0, 0, 0, 0, 1, 1,
      0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // 0.125 = 0.001 = 1e-3
  // exponent = -3 + 127(bias) = 124
  array<int,S> arr3
    { 0, // positive
      0, 1, 1, 1, 1, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // -70.2 = 1000110.00110011001100... = 1.00011000110011001100...e6
  // exponent = 6 + 127(bias) = 133
  array<int,S> arr4
    { 1, // negative
      1, 0, 0, 0, 0, 1, 0, 1,
      0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0 };


  // 0.0 = 0.0 = 0.0e0
  // if exponent is zero leading 1 is not ignored
  array<int,S> arr5
    { 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  // -----------------------------------------------------------------------

  array<int,S> first
    { 0,
      1, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  array<int,S> second
    { 0,
      1, 0, 0, 0, 0, 0, 1, 1,
      0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  array<int,S> firstSecondSum
    { 0,
      1, 0, 0, 0, 0, 1, 0, 0,
      1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


  array<int,S> sum = addFloats(first,second);
  assert(sum == addFloats(second,first));
  assert(sum == firstSecondSum);

}

int getExponentValue(const array<int,S> & arr){
  return baseToValue(getRawExponent(arr),2) - 127;
}

vecstr getRawExponent(const array<int,S> & arr){
  vecstr e(8);
  for(int i=0;i<8;i++){ e.at(i) = to_string(arr.at(i+1)); }
  return e;
}

vecstr getMantissa(const array<int,S> & arr){

  int lastDigitIndex = arr.size()-1;
  while(lastDigitIndex>8 && arr.at(lastDigitIndex)==0){
    lastDigitIndex--;
  }

  vecstr mantissa(lastDigitIndex - 7);

  // If exponent is not 0 leading 1 is implicit
  mantissa.at(0) = "1";
  for(int i=1;i<mantissa.size();i++){
    mantissa.at(i) = to_string(arr.at(i+8));
  }

  return mantissa;
}

array<int,S> addFloats(const array<int,S> & first, const array<int,S> & second){

  int firstExponent = getExponentValue(first);
  int secondExponent = getExponentValue(second);

  vecstr exponent = getRawExponent(firstExponent>secondExponent ? first : second);
  assert(exponent.size() == 8);

  vecstr firstMantissa = getMantissa(first);
  vecstr secondMantissa = getMantissa(second);

  int diff = abs(firstExponent-secondExponent);

  // Shift to make exponents equal
  if(firstExponent>secondExponent){
    secondMantissa.insert(secondMantissa.end(),diff,"0");
  }else if(firstExponent<secondExponent){
    firstMantissa.insert(firstMantissa.end(),diff,"0");
  }

  vecstr resultMantissa = addBinary(firstMantissa,secondMantissa);

  // Initialize vector with zeros
  vecstr sum(S,"0");

  // Set exponent
  std::copy(exponent.begin(),exponent.end(),sum.begin()+1);

  // Set mantissa
  std::copy(resultMantissa.begin()+1,resultMantissa.end(),sum.begin()+9);

  array<int,S> result;
  for(int i=0;i<S;i++){ result.at(i) = stoi(sum.at(i)); }

  return result;
}
