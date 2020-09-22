#ifndef FUNCTIONS__H__
#define FUNCTIONS__H__

#include <string>
#include <vector>

using std::vector;
using std::string;
using std::to_string;

typedef vector<string> vecstr;

vecstr numberToBase(int number,int base);
int baseToValue(vecstr str,int base);
vecstr addBinary(vecstr a,vecstr b);
string notc(string str);
vecstr convertBase(vecstr,int,int);

#endif
