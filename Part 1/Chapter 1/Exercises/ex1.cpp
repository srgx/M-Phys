#include <cassert>
#include "../Programs/numbers_functions.h"

int main(){

  // Bin to Hex
  assert(convertBase(vecstr({ "1", "0", "0", "0", "1", "0", "1" }), 2, 16) ==
                     vecstr({ "4", "5" }));
  assert(convertBase(vecstr({ "1", "0", "1", "0", "1", "1", "1", "1", "0", "1", "1", "0" }), 2, 16) ==
                     vecstr({ "10", "15", "6" }));

  // Hex to Bin
  assert(convertBase(vecstr({ "4", "5" }), 16, 2) ==
                     vecstr({ "1", "0", "0", "0", "1", "0", "1" }));
  assert(convertBase(vecstr({ "10", "15", "6" }), 16, 2) ==
                     vecstr({ "1", "0", "1", "0", "1", "1", "1", "1", "0", "1", "1", "0" }));

  // Dec to Bin
  assert(convertBase(vecstr({ "6", "9" }), 10, 2) ==
                     vecstr({ "1", "0", "0", "0", "1", "0", "1" }));
  assert(convertBase(vecstr({ "2", "1", "4" }), 10, 2) ==
                     vecstr({ "1", "1", "0", "1", "0", "1", "1", "0" }));

  // Bin to Dec
  assert(convertBase(vecstr({ "1", "0", "0", "0", "1", "0", "1" }), 2, 10) ==
                     vecstr({ "6", "9" }));
  assert(convertBase(vecstr({ "1", "0", "1", "0", "0", "1", "1", "0", "1" }), 2, 10) ==
                     vecstr({ "3", "3", "3" }));



  // Other Conversions

  assert(convertBase(vecstr({ "1", "1", "3", "2" }), 8, 12) ==
                     vecstr({ "4", "2", "2" }));

  assert(convertBase(vecstr({ "6", "3", "4", "5" }), 10, 33) ==
                     vecstr({ "5", "27", "9" }));

  assert(convertBase(vecstr({ "7", "8", "6" }), 36, 4) ==
                     vecstr({ "2", "1", "0", "2", "1", "1", "2" }));

  assert(convertBase(vecstr({ "6", "1", "2" }), 24, 33) ==
                     vecstr({ "3", "6", "17" }));


  std::cout << "Part 1 - Chapter 1 - Exercise 1\n";

}
