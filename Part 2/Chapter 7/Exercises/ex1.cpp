#include <iostream>
#include <iomanip>
#include "../Programs/energy_functions.h"


using std::cout;
using std::endl;


int main(){

  cout << std::setprecision(2);
  
  const float initialAngle { 0.8 };
  const float initialSpeed { 25 };
  const float step { 0.5 };
  const float seconds { 3.5 };
  
  for(float i=0;i<=seconds;i+=step){
    
    auto result = javelin(initialAngle,initialSpeed,i);
    
    cout << "After " << i << " seconds:\n";
    
    cout << "  Position: ";
    cout << result.first.at(0) << ", ";
    cout << result.first.at(1) << endl;
    
    cout << "  Angle: ";
    cout << result.second << " radians (" << radToDeg(result.second) << " degrees)" << endl;
    
  }
  
  std::cout << "Part 2 - Chapter 7 - Exercise 1\n";
  
}

