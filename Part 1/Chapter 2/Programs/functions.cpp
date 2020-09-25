#include <cmath>
#include <vector>
#include "functions.h"

fraction addFractions(fraction f1, fraction f2){

  int num1 = f1.numerator; int den1 = f1.denominator;
  int num2 = f2.numerator; int den2 = f2.denominator;

  if(den1 == den2){
    return { num1 + num2, den1 };
  }else{
    int num3 = num1 * den2;
    int num4 = num2 * den1;
    return { num3 + num4, den1 * den2 };
  }

}

std::vector<int> listOfPrimes(int m){

  std::vector<int> nlist(m-1);

  for(int i=0;i<m-1;i++){ nlist.at(i) = i + 2; }

  int maxM = floor(sqrt(m)); int index = 0;

  while(nlist[index] <= maxM || nlist[index] == 0){

    // Skip deleted number
    if(nlist[index] == 0){ index++; continue; }

    int prime = nlist[index];

    for(int index2 = index + 1; index2 < m-1; index2++){
      if(nlist.at(index2) % prime == 0){
        nlist.at(index2) = 0; // delete
      }
    }

    index++;
  }

  std::vector<int> result;
  for(const int & val : nlist){
    if(val != 0){ result.push_back(val); }
  }

  return result;
}
