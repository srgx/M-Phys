#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef vector<string> vecstr;

vecstr numberToBase(int,int);
int baseToValue(vecstr,int);
vecstr addBinary(vecstr,vecstr);
string notc(string);

int main(){

  vecstr resultv = numberToBase(69,2);

  for(const auto & value : resultv){
    cout << value << ' ';
  }

  cout << '\n';

  vecstr str1 { "1", "0", "0", "0", "1", "0", "1" };
  int resultn = baseToValue(str1,2);
  cout << resultn << '\n';

  vecstr str2 { "1", "0", "1" };

  vecstr sm = addBinary(str1,str2);

  for(const auto & value : sm){
    cout << value << ' ';
  }

  cout << '\n';

}

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
  int asize = a.size(); int bsize = b.size(); int diff = abs(asize-bsize);

  if(asize>bsize){
    b.insert(b.begin(),diff,"0");
  }else if(bsize>asize){
    a.insert(a.begin(),diff,"0");
  }

  vecstr output; string carryD = "0";
  for(int i = asize - 1; i >= 0; i--){
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
