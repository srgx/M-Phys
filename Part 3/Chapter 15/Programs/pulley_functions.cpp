#include <cmath>
#include "pulley_functions.h"

float getRocketSpeed(float currentSpeed,
                     float currentMass,
                     float massBurned,
                     float fuelVelocity,
                     float gravity,
                     float time){

  return currentSpeed +
         fuelVelocity * log(currentMass/(currentMass - massBurned)) -
         gravity * time;

}


float getRocketPosition(float currentPosition,
                        float currentSpeed,
                        float currentMass,
                        float massBurnRate,
                        float fuelVelocity,
                        float gravity,
                        float time){

  float massBurned = time * massBurnRate;

  float speed = getRocketSpeed(currentSpeed,currentMass,
                               massBurned,fuelVelocity,
                               gravity,time);

  return currentPosition + time * speed;

}

