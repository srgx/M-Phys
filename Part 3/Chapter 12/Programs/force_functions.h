#ifndef FORCE_FUNCTIONS__H__
#define FORCE_FUNCTIONS__H__
#include <array>

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

typedef std::array<double,2> v2d;

double distance(v2d a,v2d b);
v2d mulVector(v2d vector,double value);
v2d divVector(v2d vector,double value);
v2d addVectors(v2d a,v2d b);
v2d subVectors(v2d a,v2d b);
v2d unitVector(v2d vector);
double vectorMagnitude(v2d vector);


double gravityForce(double mass1, double mass2, double distance);
double earthForce(double mass);
double orbitalPeriod(double totalMass,double semiMajorAxis);
double ellipticOrbitalSpeed(double semiMajorAxis,double distance);
double centripetalForce(double mass, double speed, double radius);
double rotationRadius(double mass,double period);
double rotationSpeed(double radius, double period);
double moveCannonBall(double currentHeight, double initialSpeed,
                      double timePeriod, double mass);


#endif
