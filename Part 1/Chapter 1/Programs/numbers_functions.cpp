#include "numbers_functions.h"
#include <algorithm>
#include <cassert>
#include <iostream>

vecstr numberToBase(int number,int base){
  if(number < base){
    return vecstr(1,to_string(number));
  }else{
    int remainder = number % base;
    string output = to_string(remainder);
    int reduced = (number - remainder) / base;
    vecstr rest = numberToBase(reduced,base);
    rest.push_back(output);
    return rest;
  }
}

int baseToValue(vecin vec,int base){
  vecstr v(vec.size());
  for(int i=0;i<v.size();i++){ v.at(i) = to_string(vec.at(i)); }
  return baseToValue(v,base);
}

int baseToValue(vecstr str,int base){
  if(str.empty()){
    return 0;
  }else{
    int output = stoi(str.back()); str.pop_back();
    int strval = baseToValue(str,base);
    return base * strval + output;
  }
}

void align(vecin & a, vecin & b){
  int diff = abs(int(a.size()-b.size()));
  if(a.size()>b.size()){
    b.insert(b.begin(),diff,0);
  }else if(b.size()>a.size()){
    a.insert(a.begin(),diff,0);
  }
}

vecin divBinary(const vecin & dividend, const vecin & divisor){
  // ...
}

vecin mulBinary(const vecin & a,const vecin & b){
  std::vector<vecin> products;
  for(int i=a.size()-1;i>=0;i--){
    vecin product;
    if(a.at(i)){
      product = b; int padding = a.size()-1-i;
      product.insert(product.end(),padding,0);
    }else{
      product = vecin({ 0 });
    }
    products.push_back(product);
  }

  vecin result = { 0 };
  for(const auto & p : products){
    result = addBinary(result,p);
  }
  return result;
}

vecin subBinary(vecin a,vecin b){

  align(a,b);

  vecin output; int carryD = 0;
  for(int i = a.size() - 1; i >= 0; i--){
    int k1 = a.at(i); int k2 = b.at(i); int writeD;
    if(k1 == k2){
      writeD = carryD;
    }else{
      writeD = notc(carryD);
      if(k1 == carryD){ carryD = notc(carryD); }
    }

    output.insert(output.begin(),writeD);
  }

  return output;

}

vecin addBinary(vecin a, vecin b){

  align(a,b);

  vecin output; int carryD = 0;
  for(int i = a.size() - 1; i >= 0; i--){
    int k1 = a.at(i); int k2 = b.at(i); int writeD;
    if(k1==k2){
      writeD = carryD; carryD = k1;
    }else{
      writeD = notc(carryD);
    }
    output.insert(output.begin(),writeD);
  }

  if(carryD==1){
    output.insert(output.begin(),1);
  }

  return output;

}

int notc(int n){
  if(n==0){
    return 1;
  }else{
    return 0;
  }
}

vecstr convertBase(vecstr str,int base1,int base2){

  vecstr result;

  if(2==base1&&16==base2){

    // Create 4 bit groups
    while(str.size()%4!=0){ str.insert(str.begin(),"0"); }

    // Convert every 4 bits to hex value
    for(int i=0;i<str.size();i+=4){
      fbits currentBins; std::copy(str.begin()+i,str.begin()+i+4, currentBins.begin());
      result.push_back(binToHex(currentBins,CONVERSION_TABLE));
    }

  }else if(16==base1&&2==base2){
    for(const auto & hx : str){
      fbits currentD = hexToBin(hx,CONVERSION_TABLE);
      result.insert(result.end(),currentD.begin(),currentD.end());
    }
  }else{
    result = numberToBase(baseToValue(str,base1),base2);
  }

  return result;
}

fbits hexToBin(const string & str,const conv & table){
  for(auto it = table.begin(); it<table.end();it++){
    if(it->first==str){ return it->second; }
  }
}

string binToHex(const fbits & fb, const conv & table){
  for(auto it = table.begin(); it<table.end();it++){
    if(it->second==fb){ return it->first; }
  }
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
