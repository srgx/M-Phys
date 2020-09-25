#include <cassert>
#include "../Programs/functions.h"

// g++ ex1.cpp ../Programs/functions.cpp

int main(){

  assert(convertBase(vecstr({ "1", "0", "0", "0", "1", "0", "1" }), 2, 16) ==
                     vecstr({ "4", "5" }));
  assert(convertBase(vecstr({ "1", "1", "3", "2" }), 8, 12) ==
                     vecstr({ "4", "2", "2" }));
  assert(convertBase(vecstr({ "6", "3", "4", "5" }), 10, 33) ==
                     vecstr({ "5", "27", "9" }));
  assert(convertBase(vecstr({ "7", "8", "6" }), 36, 4) ==
                     vecstr({ "2", "1", "0", "2", "1", "1", "2" }));

}
