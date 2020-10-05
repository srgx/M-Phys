#ifndef FUNCTIONS__H__
#define FUNCTIONS__H__

#include <string>
#include <vector>

using std::string;
using std::to_string;

typedef std::vector<string> vecstr;
typedef std::vector<int> vecin;

vecstr numberToBase(int number,int base);
int baseToValue(vecstr str,int base);
int baseToValue(vecin vec,int base);
vecin addBinary(vecin a,vecin b);
vecin subBinary(vecin a,vecin b);
void align(vecin & a, vecin & b);
int notc(int n);
vecstr convertBase(vecstr,int,int);

#endif
