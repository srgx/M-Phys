#include <cassert>
#include "numbers_functions.h"
#include <iostream>

// g++ numbers.cpp numbers_functions.cpp

int main(){

  assert(numberToBase(69,2) == vecstr({ "1", "0", "0", "0", "1", "0", "1" }));
  assert(numberToBase(134,8) == vecstr({ "2", "0", "6" }));
  assert(numberToBase(5234,14) == vecstr({ "1", "12", "9", "12" }));
  assert(numberToBase(399,16) == vecstr({ "1", "8", "15" }));

  assert(baseToValue(vecstr({ "1", "1", "0", "0", "0", "0" }),2) == 48);
  assert(baseToValue(vecstr({ "1", "0", "0", "4" }),8) == 516);
  assert(baseToValue(vecstr({ "2", "13", "3", "5" }),14) == 8083);
  assert(baseToValue(vecstr({ "11", "12", "12" }),16) == 3020);

  assert(addBinary(vecin({ 1, 0, 1, 0, 1, 0, 1, 0 }),
                   vecin({ 1, 1, 0, 0, 1, 1, 0, 0 })) ==
                   vecin({ 1, 0, 1, 1, 1, 0, 1, 1, 0 }));
  assert(addBinary(vecin({ 1, 0, 0, 0 }),
                   vecin({ 1, 1, 1, 0, 1, 0, 0 })) ==
                   vecin({ 1, 1, 1, 1, 1, 0, 0 }));
  assert(addBinary(vecin({ 1, 1, 1, 0, 1, 0, 0 }),
                   vecin({ 1, 0, 0, 0 })) ==
                   vecin({ 1, 1, 1, 1, 1, 0, 0 }));
  assert(addBinary(vecin({ 1, 1, 0, 0, 1, 0, 1, 0 }),
                   vecin({ 1, 1, 1, 0, 1 })) ==
                   vecin({ 1, 1, 1, 0, 0, 1, 1, 1 }));


  assert(subBinary(vecin({ 1, 0, 0, 0, 1, 0, 1 }),
                   vecin({ 0, 0, 0, 1, 1, 0, 0 })) ==
                   vecin({ 0, 1, 1, 1, 0, 0, 1 }));
  assert(subBinary(vecin({ 1, 1, 1, 1, 1, 0, 1, 0 }),
                   vecin({ 1, 1, 0, 0, 1, 1, 0, 0 })) ==
                   vecin({ 0, 0, 1, 0, 1, 1, 1, 0 }));
  assert(subBinary(vecin({ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 }),
                   vecin({ 1, 1, 0, 1, 1, 1 })) ==
                   vecin({ 0, 1, 1, 1, 1, 0, 1, 0, 0, 0 }));


  assert(mulBinary(vecin({ 0 }),
                   vecin({ 1, 1, 1 })) ==
                   vecin({ 0 }));
  assert(mulBinary(vecin({ 1, 1, 1 }),
                   vecin({ 0 })) ==
                   vecin({ 0, 0, 0 }));
  assert(mulBinary(vecin({ 1, 0, 1 }),
                   vecin({ 1, 1 })) ==
                   vecin({ 1, 1, 1, 1 }));
  assert(mulBinary(vecin({ 1, 1, 1 }),
                   vecin({ 1, 0, 0, 0 })) ==
                   vecin({ 1, 1, 1, 0, 0, 0 }));


  divBinary(vecin({ 1, 0, 0, 1, 1, 1 }),
            vecin({ 1, 1 }));




}
