#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

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


void setVals(trdata & str, float startTime,
             arf stopPosition, arf startPosition);

arf calculateDisplacement(const arf & a, const arf & b);

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
         
  std::cout << "Part 1 - Chapter 5 - Exercise 2\n";
  

}


trdata calculateTraj(arf oldLocation,arf newLocation,
                     float travelTime, float currentTime){


  trdata result;

  if(0==travelTime){
    //
  }else{

    // Total displacement
    result.displacement = calculateDisplacement(oldLocation,newLocation);

    // Displacement per second
    result.velocity = arf({ result.displacement.at(0)/travelTime,
                            result.displacement.at(1)/travelTime });
        
    setVals(result,currentTime,newLocation,oldLocation);

  }

  return result;

}


trdata calculateTrajectory(arf oldPosition, arf newPosition,
                           float speed, float currentTime){
  
  trdata result;
  
  if(0==speed){
    //
  }else{
    
    // Total displacement
    result.displacement = calculateDisplacement(oldPosition,newPosition);
    
    const float distance =
      sqrt(pow(result.displacement.at(0),2)+
           pow(result.displacement.at(1),2));
    
    const float travelTime = distance/speed;
    
    
    // Displacement per second
    result.velocity = arf({ result.displacement.at(0)/travelTime,
                            result.displacement.at(1)/travelTime });
    
    setVals(result,currentTime,newPosition,oldPosition);
    
  }
  
  return result;
  
}

void setVals(trdata & str, float startTime,
             arf stopPosition, arf startPosition){
  
  str.startTime = startTime;
  str.stopPosition = stopPosition;
  str.startPosition = startPosition;
               
}

arf calculateDisplacement(const arf & a, const arf & b){
  return { b.at(0) - a.at(0),b.at(1) - a.at(1) } ;
}


