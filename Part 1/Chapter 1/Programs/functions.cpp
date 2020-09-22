#include "functions.h"

vecstr numberToBase(int number,int base){
  if(number < base){
    return vecstr(1,to_string(number));
  }else{
    int remainder = number % base;
    string output = to_string(remainder);
    int reduced = (number - remainder) / base;
    vecstr rest = numberToBase(reduced,base);
    rest.push_back(output);
    return rest;
  }
}

int baseToValue(vecstr str,int base){
  if(str.empty()){
    return 0;
  }else{
    int output = stoi(str.back()); str.pop_back();
    int strval = baseToValue(str,base);
    return base * strval + output;
  }
}

vecstr addBinary(vecstr a,vecstr b){
  int diff = abs(int(a.size()-b.size()));

  if(a.size()>b.size()){
    b.insert(b.begin(),diff,"0");
  }else if(b.size()>a.size()){
    a.insert(a.begin(),diff,"0");
  }

  vecstr output; string carryD = "0";
  for(int i = a.size() - 1; i >= 0; i--){
    string k1 = a.at(i); string k2 = b.at(i);
    string writeD;
    if(k1==k2){
      writeD = carryD; carryD = k1;
    }else{
      writeD = notc(carryD);
    }
    output.insert(output.begin(),writeD);
  }

  if(carryD=="1"){
    output.insert(output.begin(),"1");
  }

  return output;

}

string notc(string str){
  if(str=="0"){
    return "1";
  }else{
    return "0";
  }
}

vecstr convertBase(vecstr str,int base1,int base2){
  int number = baseToValue(str,base1);
  return numberToBase(number,base2);
}
