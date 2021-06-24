#include <cmath>
#include "force_functions.h"

double gravityForce(double mass1, double mass2, double distance){
  return G * mass1 * mass2 / pow(distance,2);
}

double earthForce(double mass){
  return g * mass;
}

double orbitalPeriod(double totalMass, double semiMajorAxis){
  return 2 * pi * sqrt(pow(semiMajorAxis,3)/(G * totalMass));
}

double ellipticOrbitalSpeed(double mass, double semiMajorAxis, double distance){
  return G * mass * ((2 * semiMajorAxis - distance) / (semiMajorAxis * distance));
}
