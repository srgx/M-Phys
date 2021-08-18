#include <iostream>
#include <cassert>
#include <iomanip>
#include "force_functions.h"

using std::cout;
using std::endl;

int main(){

  std::cout << std::setprecision(6);

  const double mass = 100;

  const double gf = gravityForce(earthMass,mass,earthRadius);
  const double ef = earthForce(mass);

  const double moonOrbitalPeriod =
    orbitalPeriod(earthMass+moonMass,moonSemiMajorAxis) /
    secondsInDay;

  cout << "F = G*m1*m2/d^2: " << gf << " N" << endl;
  cout << "F = m*g: " << ef << " N" << endl;

  cout << "Earth rotation speed: " <<
          rotationSpeed(earthRadius, secondsInDay) <<
          " meters per second" << endl;

  cout << "Moon orbital period: " <<
          moonOrbitalPeriod << " days" << endl;

  cout << "Geostationary orbit height: " <<
          (rotationRadius(earthMass,secondsInDay) - earthRadius) / 1e3 << " km" << endl;

  assert(std::abs(gf-ef) < 2);
  assert(std::abs(moonOrbitalPeriod-moonOrbitalPeriodDays) < 0.1);

  cout << "Part 3 - Chapter 12 - Force\n";

}
