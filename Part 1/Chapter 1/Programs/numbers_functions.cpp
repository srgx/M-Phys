#include "numbers_functions.h"
#include <algorithm>
#include <iostream>
#include <cassert>

using std::string;

vecstr numberToBase(int number,int base){
  if(number < base){
    return vecstr(1,std::to_string(number));
  }else{
    int remainder = number % base;
    string output = std::to_string(remainder);
    int reduced = (number - remainder) / base;
    vecstr rest = numberToBase(reduced,base);
    rest.push_back(output);
    return rest;
  }
}

vecin numberToBinary(int number){
  vecin result;
  vecstr ve = numberToBase(number,2);
  for(const auto & v : ve){
    result.push_back(stoi(v));
  }

  return result;
}

int baseToValue(vecin vec,int base){
  vecstr v(vec.size());
  for(int i=0;i<v.size();i++){ v.at(i) = std::to_string(vec.at(i)); }
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

int getBinValue(vecin vec){
  return baseToValue(vec,2);
}

vecin divBinary(const vecin & dividend,const vecin & divisor){

  vecin result; const int divisorValue = getBinValue(divisor);
  vecin currentSubNumber({ dividend.at(0) });
  int subNumberValue = getBinValue(currentSubNumber);

  for(int index = 1;index < dividend.size();index++){

    if(divisorValue > subNumberValue){
      result.push_back(0);
    }else{
      result.push_back(1);
      currentSubNumber = subBinary(currentSubNumber,divisor);
    }

    currentSubNumber.push_back(dividend.at(index));
    subNumberValue = getBinValue(currentSubNumber);

  }

  result.push_back(divisorValue<=subNumberValue ? 1 : 0);

  removeZeros(result);

  return result;
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

  vecin output = { 0 };
  for(const auto & p : products){
    output = addBinary(output,p);
  }

  removeZeros(output);

  return output;
}

int compBin(const vecin & a, const vecin & b){

  assert(a.size()==b.size());

  for(int i=0;i<a.size();i++){
    if(a.at(i)>b.at(i)){
      return 0; // First Larger
    }else if(a.at(i)<b.at(i)){
      return 1; // Second Larger
    }
  }

  return 2; // Equal
}

vecin subBinary(vecin a,vecin b){

  int comp = alignComp(a,b);

  if(comp==1){
    // Change subtraction order
    vecin temp = a; a = b; b = temp;
  }else if(comp==2){
    // Numbers are equal
    return vecin({ 0 });
  }

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

  removeZeros(output);

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

  // Remove leading zeros
  while(result.at(0)=="0"){ result.erase(result.begin()); }

  return result;
}

fbits hexToBin(const string & str,const conv & table){
  fbits result;
  for(auto it = table.begin(); it<table.end();it++){
    if(it->first==str){ result = it->second; break; }
  }
  return result;
}

string binToHex(const fbits & fb, const conv & table){
  string result;
  for(auto it = table.begin(); it<table.end();it++){
    if(it->second==fb){ result = it->first; break; }
  }
  return result;
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

iefloat divFloats(const iefloat & first, const iefloat & second){

  if(first==ZERO_F||second==ZERO_F){ return ZERO_F; }

  // Add bias before subtraction to avoid negative values
  vecin biasedFirst = addBinary(getRawExponent(first),bias); // + 127

  // Calculate exponent
  vecin exponent = subBinary(biasedFirst,getRawExponent(second));

  // Fill exponent with zeros
  exponent.insert(exponent.begin(),8-exponent.size(),0);


  // Get mantissae
  vecin firstMantissa = getMantissa(first);
  vecin secondMantissa = getMantissa(second);

  vecin resultMantissa = divBinary(firstMantissa,secondMantissa);

  // Initialize number with zeros
  iefloat result = ZERO_F;

  // Set exponent
  std::copy(exponent.begin(),exponent.end(),result.begin()+1);

  // Set mantissa
  std::copy(resultMantissa.begin()+1,resultMantissa.end(),result.begin()+9);

  int fSign = first.at(0); int sSign = second.at(0);

  // Set sign
  result.at(0) = fSign==1&&sSign==1 || fSign==0&&sSign==0 ? 0 : 1;

  return result;
}

iefloat mulFloats(const iefloat & first, const iefloat & second){

  if(first==ZERO_F||second==ZERO_F){ return ZERO_F; }

  // Calculate exponent
  vecin exponent = addBinary(getRawExponent(first),
                             getRawExponent(second));
  exponent = subBinary(exponent,bias); // - 127

  // Get mantissae
  vecin firstMantissa = getMantissa(first);
  vecin secondMantissa = getMantissa(second);

  vecin resultMantissa = mulBinary(firstMantissa,secondMantissa);

  // Initialize number with zeros
  iefloat result = ZERO_F;

  // Set exponent
  std::copy(exponent.begin(),exponent.end(),result.begin()+1);

  // Set mantissa
  std::copy(resultMantissa.begin()+1,resultMantissa.end(),result.begin()+9);

  int fSign = first.at(0); int sSign = second.at(0);

  // Set sign
  result.at(0) = fSign==1&&sSign==1 || fSign==0&&sSign==0 ? 0 : 1;


  return result;
}

iefloat subFloats(const iefloat & first, const iefloat & second){

  // Numbers are equal
  if(first==second){
    return ZERO_F;

  // First number is zero
  }else if(first==ZERO_F){
    iefloat result = second; result.at(0) = notc(second.at(0));
    return result;

  // Second number is zero
  }else if(second==ZERO_F){
    return first;
  }

  // Get mantissae
  vecin firstMantissa = getMantissa(first);
  vecin secondMantissa = getMantissa(second);

  int firstExponent = getExponentValue(first);
  int secondExponent = getExponentValue(second);

  // Difference between exponents(shift)
  int diff = std::abs(firstExponent-secondExponent);

  int firstMantissaLength = firstMantissa.size();
  int secondMantissaLength = secondMantissa.size();


  vecin exponent;

  // "Add" zeros at the beginning of mantissa to make exponents equal(shift mantissae)
  // Larger exponent is result exponent
  if(firstExponent>secondExponent){
    secondMantissaLength += diff;
    exponent = getRawExponent(first);
  }else{
    firstMantissaLength += diff;
    exponent = getRawExponent(second);
  }

  diff = std::abs(firstMantissaLength-secondMantissaLength);

  // Add zeros at the end
  if(firstMantissaLength>secondMantissaLength){
    secondMantissa.insert(secondMantissa.end(),diff,0);
  }else if(firstMantissaLength<secondMantissaLength){
    firstMantissa.insert(firstMantissa.end(),diff,0);
  }

  int fSign = first.at(0); int sSign = second.at(0);

  vecin resultMantissa =
    (1==fSign&&1==sSign||0==fSign&&0==sSign) ?
      subBinary(firstMantissa,secondMantissa) : // Same signs
      addBinary(firstMantissa,secondMantissa); // Opposite signs

  // Normalize exponent
  exponent =
    normalizeExponent(exponent, firstMantissa, secondMantissa,resultMantissa);

  // Initialize number with zeros
  iefloat result = ZERO_F;

  // Set exponent
  std::copy(exponent.begin(),exponent.end(),result.begin()+1);

  // Set mantissa
  std::copy(resultMantissa.begin()+1,resultMantissa.end(),result.begin()+9);

  // Compare numbers
  int comp = alignComp(firstMantissa,secondMantissa);


  // Set sign

  result.at(0) =
    0 == fSign ?

      // First number is positive
      // Positive result if secondMantissa<=firstMantissa or second sign is negative
      (((0==comp||2==comp) || 1==sSign) ? 0 : 1) :

      // First number is negative
      // Positive result if secondMantissa>=firstMantissa and second sign is negative
      (((1==comp||2==comp) && 1==sSign) ? 0 : 1);

  return result;
}


iefloat addFloats(const iefloat & first, const iefloat & second){

  if(first==ZERO_F){
    return second;
  }else if(second==ZERO_F){
    return first;
  }

  int firstExponent = getExponentValue(first);
  int secondExponent = getExponentValue(second);

  // Get mantissae
  vecin firstMantissa = getMantissa(first);
  vecin secondMantissa = getMantissa(second);

  vecin exponent;

  // Difference between exponents(shift)
  int diff = std::abs(firstExponent-secondExponent);

  int firstMantissaLength = firstMantissa.size();
  int secondMantissaLength = secondMantissa.size();

  // "Add" zeros at the beginning of mantissa to make exponents equal(shift mantissae)
  // Larger exponent is result exponent
  if(firstExponent>secondExponent){
    secondMantissaLength += diff;
    exponent = getRawExponent(first);
  }else{
    firstMantissaLength += diff;
    exponent = getRawExponent(second);
  }

  diff = std::abs(firstMantissaLength-secondMantissaLength);

  // Add zeros at the end
  if(firstMantissaLength>secondMantissaLength){
    secondMantissa.insert(secondMantissa.end(),diff,0);
  }else if(firstMantissaLength<secondMantissaLength){
    firstMantissa.insert(firstMantissa.end(),diff,0);
  }

  int fSign = first.at(0); int sSign = second.at(0);

  vecin resultMantissa =
    (1==fSign&&1==sSign||0==fSign&&0==sSign) ?
      addBinary(firstMantissa,secondMantissa) : // Same signs
      subBinary(firstMantissa,secondMantissa); // Opposite signs

  // Normalize exponent
  exponent =
    normalizeExponent(exponent, firstMantissa, secondMantissa,resultMantissa);

  // Initialize number with zeros
  iefloat result = ZERO_F;

  // Set exponent
  std::copy(exponent.begin(),exponent.end(),result.begin()+1);

  // Set mantissa
  std::copy(resultMantissa.begin()+1,resultMantissa.end(),result.begin()+9);

  // Compare numbers
  int comp = alignComp(firstMantissa,secondMantissa);

  // Set sign

  result.at(0) =
    0 == fSign ?

      // First number is positive
      // Positive result if secondMantissa<=firstMantissa or second sign is positive
      (((0==comp||2==comp) || 0==sSign) ? 0 : 1) :

      // First number is negative
      // Positive result if secondMantissa>=firstMantissa and second sign is positive
      (((1==comp||2==comp) && 0==sSign) ? 0 : 1);

  return result;
}

iefloat negateFloat(iefloat n){
  n.at(0) = notc(n.at(0)); return n;
}


vecin normalizeExponent(const vecin & exponent, const vecin & firstMantissa, const vecin & secondMantissa, const vecin & resultMantissa){

  const int fms = firstMantissa.size(); const int sms = secondMantissa.size();

  // Find size of larger factor
  const int resultSize = fms > sms ? fms : sms;

  // Calculate how many zeros are at the beginning
  const int sizeDiff = resultSize - resultMantissa.size();

  // Set exponent according to number of zeros
  return subBinary(exponent,numberToBinary(sizeDiff));

}

int alignComp(vecin & a, vecin & b){
  align(a,b); return compBin(a,b);
}

// Add zeros at the beginning
void align(vecin & a, vecin & b){
  int diff = std::abs(int(a.size()-b.size()));
  if(a.size()>b.size()){
    b.insert(b.begin(),diff,0);
  }else if(b.size()>a.size()){
    a.insert(a.begin(),diff,0);
  }
}


void removeZeros(vecin & number){
  // Remove leading zeros
  while(number.at(0)==0&&number.size()>1){ number.erase(number.begin()); }
}
