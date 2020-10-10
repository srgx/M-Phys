#include "algebra_functions.h"
#include "../../Chapter 2/Programs/arithmetic_functions.h"
#include <cmath>

compare::compare(const float & i) : key(i) {}

bool compare::operator()(const float & i){
  // "std::abs", not "abs"
  return (std::abs(i-key)<1e-5);
}

vecflt solveCubic(float a, float b, float c, float d){

  if(d!=1){ a/=d; b/=d; c/=d; }

  float p = b/3 - pow(a,2)/9;
  float q = pow(a,3)/27 - a*b/6 + c/2;
  float disc = pow(p,3) + pow(q,2);

  vecflt ret;

  if(disc>=0){
    rootres re = mthRoot((-q+sqrt(disc)),3);
    float r = re.result;
    if(disc==0){
      ret = vecflt({ 2*r, -r });
    }else{
      rootres ru = mthRoot((-q-sqrt(disc)),3);
      float s = ru.result;
      ret = vecflt({ r + s });
    }
  }else{
    float ang = acos(-q/sqrt(-p*p*p));
    float r = 2 * sqrt(-p);
    for(int k=-1;k<2;k++){
      float theta = (ang-2*M_PI*k)/3;
      ret.push_back(r*cos(theta));
    }
  }

  for(auto & v : ret){ v -= a/3; }

  return ret;
}
