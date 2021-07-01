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

double centripetalForce(double mass, double speed, double radius){
  return mass * pow(speed,2) / radius;
}

double rotationRadius(double mass,double period){
  return std::cbrt(mass * G * pow(period,2) / (4 * pow(pi,2)));
}

double rotationSpeed(double radius, double period){
  return 2 * pi * radius / period;
}

double moveCannonBall(double currentHeight, double initialSpeed,
                      double timePeriod, double mass){
  double currentSpeed = sqrt(2 * G * mass / currentHeight - pow(initialSpeed,2));
  return currentSpeed * timePeriod;
}
