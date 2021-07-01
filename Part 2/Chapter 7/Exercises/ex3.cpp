#include <iostream>
#include "../Programs/energy_functions.h"

using std::cout;
using std::endl;

int main(){
  
  // Cannon and ball mass
  const float massOfBall { 2 };
  const float massOfCannon { 200 } ;

  // Chemical energy from gunpowder
  const float totalEnergy { 909 } ;
  
  auto speed =
    fireCannon(massOfBall,massOfCannon,totalEnergy);
  
  cout << "Speed of ball: " << speed.at(0) << endl;
  cout << "Speed of cannon: " << speed.at(1) << endl;
  
  std::cout << "Part 2 - Chapter 7 - Exercise 3\n";
  
}
