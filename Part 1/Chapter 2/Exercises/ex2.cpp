#include <cassert>
#include "../Programs/functions.h"

// g++ ex2.cpp ../Programs/functions.cpp

int main(){

  const float INITIAL_CASH = 1000;
  const float INTEREST_RATE = 3;
  const int YEARS = 10;
  const float AMOUNTS [YEARS] =
    { 1030, 1060.9, 1092.73, 1125.51, 1159.27,
      1194.05,1229.87,1266.77, 1304.77, 1343.92 };

  float currentAmount = INITIAL_CASH;
  for(int i=0;i<YEARS;i++){
    currentAmount = compoundInterest(currentAmount,INTEREST_RATE,1);
    assert(abs(currentAmount-AMOUNTS[i])<0.01);
  }

}
