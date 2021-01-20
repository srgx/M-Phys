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
  return stoi(substituteNoX(substituteX(str,valX)));
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

// Process expression without variable
std::string substituteNoX(const std::string & str){
  return addSub(mulDiv(expo(substituteParens(str))));
}

std::string substituteParens(const std::string & str){

  int index = 0; std::string newString;

  while(index<str.size()){

    if(str.at(index)!='('){
      
      newString.push_back(str.at(index)); index++;

    }else{

      int lastIndex = findLastParenIndex(str,index);

      auto subexp = str.substr(index+1,lastIndex-(index+1));

      auto sb = substituteNoX(subexp);

      if(index!=0){

        auto prv = str.at(index-1);
        if(std::isdigit(prv)||')'==prv){
          newString.push_back('*');
        }

      }

      newString += sb;

      index = lastIndex+1;

    }
  }

  return newString;
}

// Process expression consisting only
// of numbers and symbols '+', '-'
std::string addSub(const std::string & str){

  int sum = 0;
  bool plus = true;

  std::string numstr;

  for(int i=0;i<str.size();i++){

    if(std::isdigit(str.at(i))){
      numstr.push_back(str.at(i));
    }else{

      int v = stoi(numstr);
      sum += plus ? v : -v;

      numstr.clear();

      plus = str.at(i)=='+';

    }

  }

  int v = stoi(numstr);
  sum += plus ? v : -v;

  return std::to_string(sum);

}

// Simplify expression consisting only
// of numbers and symbols '+', '-', '*', '/'
std::string mulDiv(const std::string & str){

  int index = 0; std::string newString;

  while(index<str.size()){

    char c = str.at(index);

    if(c!='*'&&c!='/'){
      newString.push_back(c);
      index++;

    // Multiplication or division found
    }else{

      // Simplify multiplication/division group
      std::pair<std::string,int> subs = onlyMulDiv(str,index);

      // Drop unnecessary chars
      while(!newString.empty()&&std::isdigit(newString.back())){
        newString.pop_back();
      }

      newString += subs.first;

      // Set index after multiplication/division group
      index = subs.second+1;

    }
  }
  
  return newString;
}

// First '*' or '/' at index
std::pair<std::string,int> onlyMulDiv(const std::string & str,int index){

  std::string lastV; int backIndex = index-1; int lastGroupIndex = index;

  // Index of last character in group
  while(lastGroupIndex<str.size()&&
        str.at(lastGroupIndex)!='-'&&
        str.at(lastGroupIndex)!='+'){
    lastGroupIndex++;
  }
  lastGroupIndex--;

  // Find first number
  while(backIndex>=0&&std::isdigit(str.at(backIndex))){
    lastV.push_back(str.at(backIndex)); backIndex--;
  }

  // First number string
  reverse(lastV.begin(), lastV.end());


  // First number value
  int totalV = stoi(lastV); lastV.clear();

  // Symbol '*' or '/'
  char s = str.at(index);

  while(index!=lastGroupIndex){

    index++;

    if(std::isdigit(str.at(index))){

      lastV.push_back(str.at(index));

    }else{

      int currentV = stoi(lastV);
      lastV.clear();

      if(s=='*'){
        totalV *= currentV;
      }else{
        totalV /= currentV;
      }

    }
  }

  int currentV = stoi(lastV);

  if(s=='*'){
    totalV *= currentV;
  }else{
    totalV /= currentV;
  }
  
  return std::make_pair(std::to_string(totalV),lastGroupIndex);

}

std::string expo(const std::string & str){
  
  int index = 0; std::string newString;

  while(index<str.size()){
    
  
    char c = str.at(index);
    

    if(c!='^'){
      newString.push_back(c);
      index++;

    // Exponentiation found
    }else{
      
      int lastIndex = index;
      
      while(lastIndex<str.size()&&
           (std::isdigit(str.at(lastIndex))||str.at(lastIndex)=='^')){
        lastIndex++;
      }
      
      lastIndex--;
      

      // Drop unnecessary chars
      while(!newString.empty()&&std::isdigit(newString.back())){
        newString.pop_back();
        index--;
      }
      
      auto group = str.substr(index,lastIndex-index+1);
      
      
      // Simplify exponentiation group
      auto subs = onlyExpo(group);
      

      newString += subs;
      
      // Set index after exponentiation
      index = lastIndex+1;
      

    }
  }

  return newString;
  
}

std::string onlyExpo(const std::string & str){
  
  std::vector<int> numbers;
  std::string currentString;
  
  for(int i=0;i<str.length();i++){
    
    if(str.at(i)!='^'){
      currentString.push_back(str.at(i));
    }else{
      numbers.push_back(stoi(currentString));
      currentString.clear();
    }
    
  }
  
  numbers.push_back(stoi(currentString));
  
  // Penultimate number
  int expoValue = numbers.back();
  
  // Index of current number
  int index = numbers.size()-2;
  
  while(index>=0){
    expoValue = pow(numbers.at(index),expoValue);
    index--;
  }
  

  return std::to_string(expoValue);
  
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


// -----------------------------------------------------------------------

// Count x terms
int countX(const std::string & str){
  
  int count = 0; int len = str.length();
  
  for(int i=0;i<len;i++){
    
    char c = str.at(i);
    
    if('x'==c){
      
      // First character is x
      if(0==i){
        count++;
      } else {
        
        std::string coef; int ind = i;
        char z;
        
        while((--ind)>=0 && std::isdigit(z=str.at(ind))){
          coef.push_back(z);
        }
        
        reverse(coef.begin(), coef.end());
        
        int n = stoi(coef);
  
        count += ind>=0&&z=='-' ? -n : n;
        
      }
      
    }
    
  }
  
  return count;
  
}

int countNums(const std::string & str){
  
  int count = 0; int len = str.length();
  
  string currentNumString; bool plus = true;
  char c;
  
  for(int i=0;i<len;i++){
    
    c = str.at(i);
    
    if(std::isdigit(c)){
      
      currentNumString.push_back(c);
      
    }else if('x'==c){
      
      currentNumString.clear();
      
    }else if('+'==c){
      
      if(!currentNumString.empty()){
      
        int cNum = stoi(currentNumString);
        currentNumString.clear();
        
        count += plus ? cNum : -cNum;

      }
      
      plus = true;
      
    }else if('-'==c){
      
      if(!currentNumString.empty()){
      
        int cNum = stoi(currentNumString);
        currentNumString.clear();
        
        count += plus ? cNum : -cNum;

      }
      
      plus = false;
      
    }
    
  }
  
  if(!currentNumString.empty()){
    
    int cNum = stoi(currentNumString);
    
    count += plus ? cNum : -cNum;
    
  }
  
  return count;
  
}

std::string groupTerms(const std::string & str){
  
  auto a = std::to_string(countX(str));
  auto b = std::to_string(countNums(str));
  
  std::string equation;
  
  equation += a;
  equation += "x+";
  equation += b;
  
  return equation;
    
}
