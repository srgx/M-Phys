#include <iostream>
#include <cmath>
#include <array>

typedef std::array<float,2> arrf;

using std::cout;
using std::endl;

arrf fireCannon(float massOfBall,
                float massOfCannon, float energy);

int main(){
  
  const float massOfBall { 2 };
  const float massOfCannon { 200 } ;
  const float totalEnergy { 909 } ;
  
  auto speed =
    fireCannon(massOfBall,massOfCannon,totalEnergy);
  
  cout << "Speed of cannonball: " << speed.at(0) << endl;
  cout << "Speed of cannon: " << speed.at(1) << endl;
  
}

arrf fireCannon(float massOfBall,
                float massOfCannon,float energy){
  
  // ballSpeed = (momentum / massOfBall)
  // cannonSpeed = (momentum / massOfCannon)
  
  // ballEnergy =
  //   (0.5 * massOfBall *
  //   (momentum / massOfBall) *
  //   (momentum / massOfBall)
  
  // cannonEnergy =
  //   (0.5 * massOfCannon *
  //   (momentum / massOfCannon) *
  //   (momentum / massOfCannon)
  
  // energy = cannonEnergy + ballEnergy
  
  float momentum =
    sqrt((energy * massOfCannon * massOfBall) /
         (0.5 * (massOfBall + massOfCannon)));
  
  float ballSpeed = momentum / massOfBall;
  float cannonSpeed = momentum / massOfCannon;
  
  return arrf({ ballSpeed, cannonSpeed });
  
}
