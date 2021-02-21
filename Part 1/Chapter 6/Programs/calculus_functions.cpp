#include "calculus_functions.h"
#include <cmath>

bool derivatives(const int & tests){

  const double delta { 1e-5 };
  const double d { 1e-3 };
  const double step { 0.5 };
  
  double value = 0;
  
  
  for(int i=0;i<tests;i++){
  
    // Gradient at x
    double currentGradient { (sin(value+delta)-sin(value))/delta };
    
    // First derivative of sin(x) is cos(x)
    double diff { std::abs(currentGradient-cos(value)) };
    if(diff>d){ return false; }
    
    // Gradient at x+delta
    double nextGradient
      { (sin(value+2*delta)-sin(value+delta))/delta };
    
    double secondGradient
      { (nextGradient-currentGradient)/delta };
      
    
    // Second derivative of sin(x) is -sin(x)
    diff = std::abs(secondGradient-(-sin(value)));
    if(diff>d){ return false; }
    
    value+=step;
    
  }
  
  return true;
  
}
