#include <cmath>
#include "energy_functions.h"

// Return distance after time
float distanceAcceleration(const float & initialSpeed,
                           const float & acceleration,
                           const float & time){
  return initialSpeed * time + acceleration * pow(time,2) / 2;
}

// Return speed after time
float speedAcceleration(const float & initialSpeed,
                        const float & acceleration,
                        const float & time){
  return initialSpeed + acceleration * time;
}
