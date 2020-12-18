#include "../Programs/vectors_functions.h"
#include <iostream>

// g++ -c ex1.cpp ../Programs/vectors_functions.cpp
// g++ ex1.o vectors_functions.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system

int main(){
  calculateTrajectory(std::vector<float>({ 2, 3 }),
                      std::vector<float>({ 4, 5 }),5);

  std::cout << "Exit\n";
}
