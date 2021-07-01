#include <cmath>
#include "energy_functions.h"

float radToDeg(float radians){
  return radians * 57.2957795;
}

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

std::pair<std::array<float,2>,float> javelin(float throwAngle,
                                             float throwSpeed, float time){

  const static float acceleration = -10;

  // Components of vector whose length is throwSpeed
  const float vertical = sin(throwAngle) * throwSpeed;
  const float horizontal = cos(throwAngle) * throwSpeed;

  // Current horizontal and vertical position of javelin
  const float javelinX = time * horizontal;
  const float javelinY = distanceAcceleration(vertical,acceleration,time);

  // Calculate angle from vector components
  // Horizontal value doesn't change
  const float currentVertical = vertical + acceleration * time;
  const float currentAngle = atan2(currentVertical,horizontal);

  return std::make_pair(std::array<float,2>({ javelinX, javelinY }), currentAngle);

}

std::array<float,2> fireCannon(float massOfBall,
                               float massOfCannon,float energy){

  // ballSpeed = momentum / massOfBall
  // ballEnergy = 0.5 * massOfBall * ballSpeed^2

  // cannonSpeed = momentum / massOfCannon
  // cannonEnergy = 0.5 * massOfCannon * cannonSpeed^2

  // totalEnergy = cannonEnergy + ballEnergy

  // Calculate momentum after equation transformation
  // Substitute speed with (momentum / mass) for cannon and ball
  float momentum = sqrt(2 * energy * massOfCannon * massOfBall /
                       (massOfCannon + massOfBall));

  float ballSpeed = momentum / massOfBall;
  float cannonSpeed = momentum / massOfCannon;

  return std::array<float,2>({ ballSpeed, cannonSpeed });

}


