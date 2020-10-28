#include <iostream>
#include <cassert>
#include <cmath>

using std::string;
using std::cout;
using std::endl;

int substitute(const string & str,int valX);
bool allDigits(const string & str);
string getSubexpFrom(const string & str,int index);
bool isExp(const string & str);

// g++ ex1.cpp

int main(){

  assert(isExp("x"));
  assert(isExp("5x"));
  assert(isExp("25x"));

  assert(substitute("x",6)==6);
  assert(substitute("3x",9)==27);
  assert(substitute("25x",4)==100);
  assert(substitute("5x+35",8)==75);
  assert(substitute("6x+2+x",5)==37);
  assert(substitute("12+4x+2x+8",2)==32);

  assert(getSubexpFrom("5x-10-2",0)=="5x");
  assert(getSubexpFrom("5x-10-2",3)=="10");
  assert(getSubexpFrom("10-12x-25x",3)=="12x");

  assert(substitute("5x-10-2",6)==18);
  assert(substitute("5x-10-2-x",6)==12);
  assert(substitute("56-4x+20",2)==68);

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

      // cout << "Znaleziono plus at " << i << endl;

      if(!accInitialized){
        acc = substitute(str.substr(0,i),valX);
        accInitialized = true;
      }

      string right = getSubexpFrom(str,i+1);
      float val = substitute(right,valX);
      // cout << "Dodaje " << acc << " + " << val << endl;
      acc += val;

    }else if('-'==str.at(i)){

      // cout << "Znaleziono minus at " << i << endl;

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
  int i; int counter = 0;
  for(i=from;i<str.length();i++){
    char s = str.at(i);
    if('+'==s||'-'==s){
      break;
    }
  }

  return str.substr(from,i-from);
}

bool isExp(const string & str){
  return (str.length()==1&&str.at(0)=='x')||
         (str.back()=='x'&&allDigits(str.substr(0,str.length()-1)));
}
