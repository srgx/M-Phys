#ifndef FORCE_FUNCTIONS__H__
#define FORCE_FUNCTIONS__H__

// Gravitational constant
const double G = 6.67408e-11;

// Standard acceleration
const double g = 9.80665;

const double pi = 3.14159265358979323846;

const int secondsInDay = 86400;

const double earthMass = 5.972e24;
const double earthRadius = 6371e3;

const double moonSemiMajorAxis = 384748e3;
const double moonMass = 7.34767309e22;

const double moonOrbitalPeriodDays = 27.3;


double gravityForce(double mass1, double mass2, double distance);
double earthForce(double mass);
double orbitalPeriod(double totalMass,double semiMajorAxis);
double ellipticOrbitalSpeed(double semiMajorAxis,double distance);


#endif
