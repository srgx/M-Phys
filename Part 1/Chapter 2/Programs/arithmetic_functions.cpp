#include <cmath>
#include <vector>
#include "arithmetic_functions.h"

using std::vector;
using std::array;

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

vector<int> listOfPrimes(int m){

  vector<int> nlist(m-1);

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

  vector<int> result;
  for(const int & val : nlist){
    if(val != 0){ result.push_back(val); }
  }

  return result;
}

vector<int> primeFactors(int n){
  auto plist = listOfPrimes(n/2);
  auto rlist = vector<int>();
  int index = 0;
  while(index < plist.size()){
    int prime = plist.at(index);
    if(n%prime==0){
      n /= prime; rlist.push_back(prime);
    }else{
      index++;
    }
  }
  return rlist;
}

int gcd(int n, int m){
  int r = n % m;
  if(r==0){
    return m;
  }else{
    return gcd(m,r);
  }
}

int lcm(int n, int m){
  return n * m / gcd(n,m);
}

int strictModulo(int n, int m){
  int r = n % m;
  if(r<0){
    return r + m;
  }else{
    return r;
  }
}

array<int,2> naiveClock(int oldHours, int oldMinutes, int addHours, int addMinutes){

  int newMinutes = oldMinutes + addMinutes;
  while(newMinutes>60){
    newMinutes -= 60;
    addHours++;
  }

  int newHours = oldHours + addHours;
  while(newHours>12){
    newHours -= 12;
  }

  return array<int,2>({ newHours, newMinutes });
}

array<int,2> cleverClock(int oldHours, int oldMinutes, int addHours, int addMinutes){
  const int newMinutes = strictModulo(oldMinutes + addMinutes, 60);
  addHours += (oldMinutes + addMinutes - newMinutes) / 60;
  const int newHours = 1 + strictModulo(oldHours + addHours - 1, 12);
  return array<int,2>({ newHours, newMinutes });
}

array<int,2> positionInGrid(int squareNumber, int numCols){
  const int positionAcross = 1 + (squareNumber-1) % numCols;
  const int positionDown = (squareNumber - squareNumber % numCols) / numCols;
  return array<int,2>({ positionDown, positionAcross });
}

float monthlyPayment(float initialAmount,float annualInterest, int years){

  const int months = 12 * years;
  float I = annualInterest / 1200 + 1;
  float Ipm = pow(I,months);

  return (initialAmount * Ipm * (I - 1)) / (Ipm - 1);
}

float debtAfterMonths(float initialAmount, float annualInterest, float perMonth, float months){

  float I = annualInterest / 1200 + 1;
  float Ipm = pow(I,months);
  float Rt = (Ipm - 1) / (I - 1);

  return (initialAmount * Ipm) - perMonth * Rt;
}

float compoundInterest(float initialAmount, float interestRate, int years){
  return initialAmount * (pow(1+(interestRate/100),years));
}

rootres mthRoot(float n,float m){
  rootres result { 0, false };
  if(n<0){
    float p = pow(-n,1.0/m);
    if(abs(pow(-p,m)-n)<0.1){
      result.result = -p;
    }else{
      result.error = true;
    }
  }else{
    result.result = pow(n,1.0/m);
  }
  return result;
}

float multiplyLog(float a, float b){
  auto n = log(a) + log(b);
  return exp(n);
}

float calculateMarkerPosition(float textPosition, float textHeight, float windowHeight){
  return textPosition / textHeight * windowHeight;
}

float calculateTextPosition(float markerPosition, float textHeight, float windowHeight){
  return markerPosition / windowHeight * textHeight;
}

float calculateMarkerHeight(float textHeight, float windowHeight){
  return pow(windowHeight,2) / textHeight;
}
