#ifndef PULLEY_FUNCTIONS__H__
#define PULLEY_FUNCTIONS__H__

float getRocketSpeed(float currentSpeed,
                     float currentMass,
                     float massBurned,
                     float fuelVelocity,
                     float gravity,
                     float time);

float getRocketPosition(float currentPosition,
                        float currentSpeed,
                        float currentMass,
                        float massBurnRate,
                        float fuelVelocity,
                        float gravity,
                        float time);

#endif
