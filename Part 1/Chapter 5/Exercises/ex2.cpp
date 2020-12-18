#include <array>
#include <cassert>
#include <cmath>

// g++ ex2.cpp

typedef std::array<float,2> arf;

struct trdata {
  arf displacement;
  arf velocity;
  float startTime;
  arf stopPosition;
  arf startPosition;
};


trdata calculateTraj(arf oldLocation, arf newLocation,
                           float travelTime, float currentTime);


trdata calculateTrajectory(arf oldPosition, arf newPosition,
                           float speed, float currentTime);

int main(){

  const float currentTime = 20;
  const float travelTime = 5;
  

  trdata result =
    calculateTraj(arf({ 3, 3 }),arf({ 8, 6 }),travelTime,currentTime);

  assert(5==result.displacement.at(0)&&
         3==result.displacement.at(1));

  assert(std::abs(result.velocity.at(0)-1)<1e-5&&
         std::abs(result.velocity.at(1)-0.6)<1e-5);

  assert(std::abs(result.startTime-currentTime)<1e-5);

  assert(std::abs(result.startPosition.at(0)-3)<1e-5&&
         std::abs(result.startPosition.at(1)-3)<1e-5);

  assert(std::abs(result.stopPosition.at(0)-8)<1e-5&&
         std::abs(result.stopPosition.at(1)-6)<1e-5);
  
  
  // --------------------------------------------------------------------------
  
  
  const float speed = 3;
  
  result = calculateTrajectory(arf({ 3, 3 }),arf({ 8, 15 }),speed,currentTime);
  
  assert(5==result.displacement.at(0)&&
         12==result.displacement.at(1));

  assert(std::abs(result.velocity.at(0)-1.153847)<1e-5&&
         std::abs(result.velocity.at(1)-2.769232)<1e-5);

  assert(std::abs(result.startTime-currentTime)<1e-5);

  assert(std::abs(result.startPosition.at(0)-3)<1e-5&&
         std::abs(result.startPosition.at(1)-3)<1e-5);

  assert(std::abs(result.stopPosition.at(0)-8)<1e-5&&
         std::abs(result.stopPosition.at(1)-15)<1e-5);
  

}


trdata calculateTraj(arf oldLocation,arf newLocation,
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


trdata calculateTrajectory(arf oldPosition, arf newPosition,
                           float speed, float currentTime){
  
  trdata result;
  
  if(0==speed){
    //
  }else{
    
    float newX = newPosition.at(0) - oldPosition.at(0);
    float newY = newPosition.at(1) - oldPosition.at(1);

    // Total displacement
    result.displacement = arf({ newX, newY });
    
    const float distance =
      sqrt(pow(result.displacement.at(0),2)+
           pow(result.displacement.at(1),2));
    
    const float travelTime = distance/speed;
    
    newX /= travelTime; newY /= travelTime;
    
    // Displacement per second
    result.velocity = arf({ newX, newY });

    result.startTime = currentTime;
    result.stopPosition = newPosition;
    result.startPosition = oldPosition;
    
  }
  
  return result;
  
}


