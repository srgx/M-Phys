#include <cassert>
#include "functions.h"

int main(){

  assert(numberToBase(69,2) == vecstr({ "1", "0", "0", "0", "1", "0", "1" }));
  assert(numberToBase(134,8) == vecstr({ "2", "0", "6" }));
  assert(numberToBase(5234,14) == vecstr({ "1", "12", "9", "12" }));
  assert(numberToBase(399,16) == vecstr({ "1", "8", "15" }));

  assert(baseToValue(vecstr({ "1", "1", "0", "0", "0", "0" }),2) == 48);
  assert(baseToValue(vecstr({ "1", "0", "0", "4" }),8) == 516);
  assert(baseToValue(vecstr({ "2", "13", "3", "5" }),14) == 8083);
  assert(baseToValue(vecstr({ "11", "12", "12" }),16) == 3020);

  assert(addBinary(vecstr({ "1", "0", "1", "0", "1", "0", "1", "0" }),
                   vecstr({ "1", "1", "0", "0", "1", "1", "0", "0" })) ==
                   vecstr({ "1", "0", "1", "1", "1", "0", "1", "1", "0" }));
  assert(addBinary(vecstr({ "1", "0", "0", "0" }),
                   vecstr({ "1", "1", "1", "0", "1", "0", "0" })) ==
                   vecstr({ "1", "1", "1", "1", "1", "0", "0" }));
  assert(addBinary(vecstr({ "1", "1", "1", "0", "1", "0", "0" }),
                   vecstr({ "1", "0", "0", "0" })) ==
                   vecstr({ "1", "1", "1", "1", "1", "0", "0" }));
  assert(addBinary(vecstr({ "1", "1", "0", "0", "1", "0", "1", "0" }),
                   vecstr({ "1", "1", "1", "0", "1" })) ==
                   vecstr({ "1", "1", "1", "0", "0", "1", "1", "1" }));

}
