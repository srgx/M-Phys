#include <iostream>
#include <cassert>

using std::string;
using std::cout;
using std::endl;

int substitute(const string & str,int valX);
bool allDigits(const string & str);

// g++ ex1.cpp

int main(){
  assert(substitute("x",6)==6);
  assert(substitute("3x",9)==27);
  assert(substitute("25x",4)==100);
  assert(substitute("5x+35",8)==75);
  assert(substitute("6x+2+x",5)==37);
  assert(substitute("12+4x+2x+8",2)==32);
}


int substitute(const string & str,int valX){

  if(allDigits(str)){
    return stoi(str);
  }

  // Number not found
  for(int i=0;i<str.length();i++){

    if('+'==str.at(i)){
      int left = substitute(str.substr(0,i),valX);
      int right = substitute(str.substr(i+1),valX);
      return left + right;
    }

  }

  // Sign not found. Expression like 1234x or x.
  if(1==str.length()){
    return valX;
  }else{
    return stoi(str.substr(0,str.length()-1)) * valX;
  }


}

bool allDigits(const string & str){
  for(auto i=str.begin();i!=str.end();i++){
    if(!std::isdigit(*i)){
      return false;
    }
  }
  return true;
}
