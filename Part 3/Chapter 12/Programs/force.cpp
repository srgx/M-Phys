#include <iostream>
#include <cassert>
#include "force_functions.h"

using std::cout;
using std::endl;

int main(){

  const double mass = 100;

  const double gf = gravityForce(earthMass,mass,earthRadius);
  const double ef = earthForce(mass);

  cout << "F = G*m1*m2/d^2: " << gf << endl;
  cout << "F = m*g: " << ef << endl;


  const double moonOrbitalPeriod =
    orbitalPeriod(earthMass+moonMass,moonSemiMajorAxis) /
    secondsInDay;

  cout << "Moon orbital period: " << moonOrbitalPeriod << " days" << endl;


  assert(std::abs(gf-ef) < 2);
  assert(std::abs(moonOrbitalPeriod-moonOrbitalPeriodDays) < 0.1);

  cout << "Force\n";
  cout << "Part 3 - Chapter 12 - Force\n";
}


