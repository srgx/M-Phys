#ifndef FUNCTIONS__H__
#define FUNCTIONS__H__

#include <string>
#include <vector>
#include <array>

using std::string;
using std::to_string;
using std::make_pair;

const int HEX_SIZE = 4;
typedef std::vector<string> vecstr;
typedef std::vector<int> vecin;
typedef std::array<string,HEX_SIZE> fbits;
typedef std::array<std::pair<string,fbits>,16> conv;

const conv CONVERSION_TABLE =
  { make_pair("0", fbits({ "0", "0", "0", "0" })),
    make_pair("1", fbits({ "0", "0", "0", "1" })),
    make_pair("2", fbits({ "0", "0", "1", "0" })),
    make_pair("3", fbits({ "0", "0", "1", "1" })),
    make_pair("4", fbits({ "0", "1", "0", "0" })),
    make_pair("5", fbits({ "0", "1", "0", "1" })),
    make_pair("6", fbits({ "0", "1", "1", "0" })),
    make_pair("7", fbits({ "0", "1", "1", "1" })),
    make_pair("8", fbits({ "1", "0", "0", "0" })),
    make_pair("9", fbits({ "1", "0", "0", "1" })),
    make_pair("10", fbits({ "1", "0", "1", "0" })),
    make_pair("11", fbits({ "1", "0", "1", "1" })),
    make_pair("12", fbits({ "1", "1", "0", "0" })),
    make_pair("13", fbits({ "1", "1", "0", "1" })),
    make_pair("14", fbits({ "1", "1", "1", "0" })),
    make_pair("15", fbits({ "1", "1", "1", "1" })) };

vecstr numberToBase(int number,int base);
int baseToValue(vecstr str,int base);
int baseToValue(vecin vec,int base);
vecin addBinary(vecin a,vecin b);
vecin subBinary(vecin a,vecin b);
void align(vecin & a, vecin & b);
int notc(int n);
vecstr convertBase(vecstr,int,int);
fbits hexToBin(const string & str, const conv & table);
string binToHex(const fbits & fb, const conv & table);

#endif
