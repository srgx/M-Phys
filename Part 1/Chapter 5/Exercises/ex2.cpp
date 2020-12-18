#include <array>
#include <cassert>

// g++ ex2.cpp

typedef std::array<float,2> arf;

struct trdata {
  arf displacement;
  arf velocity;
  float startTime;
  arf stopPosition;
  arf startPosition;
};

trdata calculateTrajectory(arf oldLocation, arf newLocation,
                           float travelTime, float currentTime);

int main(){

  const float currentTime = 20;
  const float travelTime = 5;

  const trdata result =
    calculateTrajectory(arf({ 3, 3 }),arf({ 8, 6 }),travelTime,currentTime);

  assert(5==result.displacement.at(0)&&
         3==result.displacement.at(1));

  assert(std::abs(result.velocity.at(0)-1)<1e-5&&
         std::abs(result.velocity.at(1)-0.6)<1e-5);

  assert(std::abs(result.startTime-currentTime)<1e-5);

  assert(std::abs(result.startPosition.at(0)-3)<1e-5&&
         std::abs(result.startPosition.at(1)-3)<1e-5);

  assert(std::abs(result.stopPosition.at(0)-8)<1e-5&&
         std::abs(result.stopPosition.at(1)-6)<1e-5);

}

trdata calculateTrajectory(arf oldLocation,arf newLocation,
                           float travelTime, float currentTime){


  trdata result;

  if(0==travelTime){
    //
  }else{

    float newX = newLocation.at(0) - oldLocation.at(0);
    float newY = newLocation.at(1) - oldLocation.at(1);

    // Total displacement
    result.displacement = arf({ newX, newY });

    newX /= travelTime; newY /= travelTime;

    // Displacement per second
    result.velocity = arf({ newX, newY });

    result.startTime = currentTime;
    result.stopPosition = newLocation;
    result.startPosition = oldLocation;

  }

  return result;

}
