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

std::string substituteX(const std::string & str,int valX){
  
  std::string newString; int index = 0;
  
  while(index<str.size()){
    
    // Char other than x
    if(str.at(index)!='x'){
      
      newString.push_back(str.at(index));
      
    // Found x
    }else{
      
      // Variable x at 0 or without coefficient
      if(index==0||!std::isdigit(str.at(index-1))){
        
        newString += std::to_string(valX);
        
      // Variable x with coefficient
      }else{
        
        int tempIndex = index-1; std::string strnum;
        
        // Go back to find coefficient
        while(tempIndex>=0&&std::isdigit(str.at(tempIndex))){
          
          // Remove previously added chars
          newString.pop_back();
          
          // Reversed coefficient
          strnum.push_back(str.at(tempIndex));
          
          // Move back
          tempIndex--;
        }
        
        // Get coefficient string
        reverse(strnum.begin(), strnum.end());
        
        newString += std::to_string(valX*stoi(strnum));
        
      }
      
    }
    
    index++;
    
  }
  
  return newString;
  
}

int substitute(const string & str,int valX){

  std::string noX = substituteX(str,valX);
  
  return 12;

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

eqResult solveSimultaneous(std::vector<vecflt> & equations){
  std::vector<vecflt> redux; const int n = equations.size();

  eqResult result({ true });
  vecflt output(n);

  for(int i=n-1;i>=0;i--){
    vecflt row;
    for(int j=i;j>=0;j--){
      if(equations.at(j).at(i)!=0){
        row = equations.at(j); break;
      }
    }

    if(row.empty()){
      // No Solution
      result.success = false; return result;
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

    float sum = 0;
    for(int j=0;j<i;j++){
      sum = redux.at(i).at(j) * output.at(j) + sum;
    }

    output.at(i) = redux.at(i).at(n) - sum;
    
  }

  // Copy solution to result
  result.answer = output;

  return result;

}

std::string substituteNoX(const std::string & str){
  std::string noPar = substituteParens(str);
  std::cout << "Nop: " << noPar << std::endl;
  
  return addSub(noPar);
}

std::string substituteParens(const std::string & str){
  
  int index = 0; std::string newString;
  
  while(index<str.size()){
    
    if(str.at(index)!='('){
      
      newString.push_back(str.at(index)); index++;
      
    }else{
      
      int lastIndex = findLastParenIndex(str,index);
      
      std::string subexp = str.substr(index+1,lastIndex-(index+1));
      
      auto sb = substituteNoX(subexp);
      
      newString += sb;
      
      index = lastIndex+1;
      
    }
  }
  
  return newString;
}

std::string addSub(const std::string & str){
  
  int sum = 0;
  bool plus = true;
  
  std::string numstr;
  
  for(int i=0;i<str.size();i++){
    
    if(std::isdigit(str.at(i))){
      numstr.push_back(str.at(i));
    }else{
      
      if(plus){
        sum += stoi(numstr);
      }else{
        sum -= stoi(numstr);
      }
      
      numstr.clear();
      
      if(str.at(i)=='+'){
        plus = true;
      }else{
        plus = false;
      }
      
    }
    
  }
  
  if(plus){
    sum += stoi(numstr);
  }else{
    sum -= stoi(numstr);
  }

  return std::to_string(sum);
  
}

int findLastParenIndex(const std::string & str, int index){
  
  int count = 1;

  while(count!=0){
    index++;
    if(str.at(index)=='('){
      count++;
    }else if(str.at(index)==')'){
      count--;
    }
  }
  
  return index;
  
}
