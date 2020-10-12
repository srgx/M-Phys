#include "algebra_functions.h"
#include "../../Chapter 2/Programs/arithmetic_functions.h"
#include <cmath>
#include <algorithm>

#include <iostream>

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

vecflt solveSimultaneous(std::vector<vecflt> & equations){
  std::vector<vecflt> redux; const int n = equations.size();
  float solution = true;


  vecflt rty;

  for(int i=n-1;i>=0;i--){
    vecflt row;
    for(int j=i;j>=0;j--){
      if(equations.at(j).at(i)!=0){
        row = equations.at(j);
        break;
      }
    }

    if(row.empty()){
      solution = false;
      break;
    }else{
      float divisor = row.at(i);

      // for(const auto & z : row){
      //   std::cout << z << ", ";
      // }

      // std::cout << "------------\n";

      equations.erase(std::remove(equations.begin(), equations.end(), row), equations.end());
      for(int j=0;j<row.size();j++){ row.at(j) /= divisor; }
      redux.insert(redux.begin(),row);

      for(int j=equations.size()-1;j>=0;j--){

        if(equations.at(j).at(i)!=0){

          float t = equations.at(j).at(i);

          for(int w=0;w<equations.at(j).size();w++){
            equations.at(j).at(w) -= redux.at(0).at(w) * t;
          }
        }
      }
    }
  }

  // for(const auto & rx : redux){
  //   for(const auto & v : rx){
  //     std::cout << v << ", ";
  //   }
  //   std::cout << "\n---------\n";
  // }

  if(!solution){
    std::cout << "No unique solution";
    return rty;
  }else{
    vecflt output(n);
    for(int i=0;i<n;i++){
      float sum = 0; int j = 0;
      while(j<i){
        sum = redux.at(i).at(j) * output.at(j) + sum;
        j++;
      }
      output.at(i) = redux.at(i).at(n) - sum;
    }
    //std::cout << "Super";
    return output;
  }




}
