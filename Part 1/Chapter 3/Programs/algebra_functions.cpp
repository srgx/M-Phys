#include "algebra_functions.h"
#include "../../Chapter 2/Programs/arithmetic_functions.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using std::string;

bool isParExp(const std::string & str){
  if('('==str.at(0)){
    return true;
  }else{
    for(int i=0;i<str.length();i++){
      if('('==str.at(i)){
        return true;
      }else if(std::isdigit(str.at(i))){
        continue;
      }else{
        return false;
      }
    }
  }
}

int substitute(const string & str,int valX){

  // Number or X expression
  if(allDigits(str)){
    return stoi(str);
  }else if(isExp(str)){
    if(1==str.length()){
      return valX;
    }else{
      return stoi(str.substr(0,str.length()-1)) * valX;
    }
  }

  int i = 0; float acc; bool accInitialized = false;

  // Number not found
  while(i<str.length()){

    if('+'==str.at(i)){

      if(!accInitialized){
        acc = substitute(str.substr(0,i),valX);
        accInitialized = true;
      }

      string right = getSubexpFrom(str,i+1);
      float val = substitute(right,valX);
      // cout << "Dodaje " << acc << " + " << val << endl;
      acc += val;

    }else if('-'==str.at(i)){

      if(!accInitialized){
        acc = substitute(str.substr(0,i),valX);
        accInitialized = true;
      }

      string right = getSubexpFrom(str,i+1);
      float val = substitute(right,valX);
      // cout << "Odejmuje " << acc << " - " << val << endl;
      acc -= val;

    }

    // else if('/'==str.at(i)){
    //   int left = substitute(str.substr(0,i),valX);
    //   int right = substitute(str.substr(i+1),valX);
    //   return left / right;
    // }else if('^'==str.at(i)){
    //   int left = substitute(str.substr(0,i),valX);
    //   int right = substitute(str.substr(i+1),valX);
    //   return pow(left,right);
    // }

    i++;
  }

  return acc;

}

bool allDigits(const string & str){
  for(auto i=str.begin();i!=str.end();i++){
    if(!std::isdigit(*i)){
      return false;
    }
  }
  return true;
}

string getSubexpFrom(const string & str,int from){
  int i; int counter = 0; int parCount = 0;
  for(i=from;i<str.length();i++){
    char s = str.at(i);
    if(('+'==s||'-'==s)&&(0==parCount)){
      break;
    }else if('('==s){
      parCount++;
    }else if(')'==s&&0==--parCount){
      i++; break;
    }
  }

  return str.substr(from,i-from);
}

bool isExp(const string & str){
  return (str.length()==1&&str.at(0)=='x')||
         (str.back()=='x'&&allDigits(str.substr(0,str.length()-1)));
}



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

  vecflt output(n);

  for(int i=n-1;i>=0;i--){
    vecflt row;
    for(int j=i;j>=0;j--){
      if(equations.at(j).at(i)!=0){
        row = equations.at(j); break;
      }
    }

    if(row.empty()){
      std::cout << "No unique solution"; return output;
    }else{

      float divisor = row.at(i);

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

  for(int i=0;i<n;i++){
    float sum = 0; int j = 0;
    while(j<i){
      sum = redux.at(i).at(j) * output.at(j) + sum;
      j++;
    }
    output.at(i) = redux.at(i).at(n) - sum;
  }

  return output;

}
