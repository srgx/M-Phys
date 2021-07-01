#ifndef ENERGY_FUNCTIONS__H__
#define ENERGY_FUNCTIONS__H__
#include <array>

float radToDeg(float radians);

float distanceAcceleration(const float & initialSpeed,
                           const float & acceleration,
                           const float & time);

float speedAcceleration(const float & initialSpeed,
                        const float & acceleration,
                        const float & time);

std::pair<std::array<float,2>,float> javelin(float throwAngle,
                                             float throwSpeed, float time);

std::array<float,2> fireCannon(float massOfBall,
                               float massOfCannon, float energy);

#endif
