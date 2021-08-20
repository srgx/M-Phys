#include <iostream>
#include <cassert>
#include "pulley_functions.h"

using std::cout;

int main(){

  const float currentSpeed = 120;
  const float currentMass = 2000;
  const float massBurned = 100;
  const float fuelVelocity = 15;
  const float gravity = 10;
  const float time = 10;
  const float currentPosition = 1000;
  const float massBurnRate = massBurned / time;

  const float rocketSpeed = getRocketSpeed(currentSpeed,
                                           currentMass,
                                           massBurned,
                                           fuelVelocity,
                                           gravity,
                                           time);

  const float rocketPosition = getRocketPosition(currentPosition,
                                                 currentSpeed,
                                                 currentMass,
                                                 massBurnRate,
                                                 fuelVelocity,
                                                 gravity,
                                                 time);


  cout << "Rocket speed: " << rocketSpeed << '\n';
  cout << "Rocket position: " << rocketPosition << '\n';

  assert(currentPosition + time * rocketSpeed == rocketPosition);

  cout << "Part 3 - Chapter 15 - Pulleys\n";

}
