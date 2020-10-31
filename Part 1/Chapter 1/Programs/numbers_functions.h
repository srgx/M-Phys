#ifndef NUMBERS_FUNCTIONS__H__
#define NUMBERS_FUNCTIONS__H__

#include <string>
#include <vector>
#include <array>

const int S = 32;
const int HEX_SIZE = 4;
typedef std::vector<std::string> vecstr;
typedef std::vector<int> vecin;
typedef std::array<std::string,HEX_SIZE> fbits;
typedef std::array<std::pair<std::string,fbits>,16> conv;
typedef std::array<int,S> iefloat;

const conv CONVERSION_TABLE =
  { std::make_pair("0", fbits({ "0", "0", "0", "0" })),
    std::make_pair("1", fbits({ "0", "0", "0", "1" })),
    std::make_pair("2", fbits({ "0", "0", "1", "0" })),
    std::make_pair("3", fbits({ "0", "0", "1", "1" })),
    std::make_pair("4", fbits({ "0", "1", "0", "0" })),
    std::make_pair("5", fbits({ "0", "1", "0", "1" })),
    std::make_pair("6", fbits({ "0", "1", "1", "0" })),
    std::make_pair("7", fbits({ "0", "1", "1", "1" })),
    std::make_pair("8", fbits({ "1", "0", "0", "0" })),
    std::make_pair("9", fbits({ "1", "0", "0", "1" })),
    std::make_pair("10", fbits({ "1", "0", "1", "0" })),
    std::make_pair("11", fbits({ "1", "0", "1", "1" })),
    std::make_pair("12", fbits({ "1", "1", "0", "0" })),
    std::make_pair("13", fbits({ "1", "1", "0", "1" })),
    std::make_pair("14", fbits({ "1", "1", "1", "0" })),
    std::make_pair("15", fbits({ "1", "1", "1", "1" })) };

vecstr numberToBase(int number,int base);
vecin numberToBinary(int number);
int baseToValue(vecstr str,int base);
int baseToValue(vecin vec,int base);
int getBinValue(vecin vec);
vecin addBinary(vecin a, vecin b);
vecin subBinary(vecin a, vecin b);
vecin mulBinary(const vecin & a, const vecin & b);
vecin divBinary(const vecin & dividend,const vecin & divisor);
void align(vecin & a, vecin & b);
int notc(int n);
vecstr convertBase(vecstr,int,int);
fbits hexToBin(const std::string & str, const conv & table);
std::string binToHex(const fbits & fb, const conv & table);
int getExponentValue(const iefloat & arr);
vecin getRawExponent(const iefloat & arr);
vecin getMantissa(const iefloat & arr);
iefloat addFloats(const iefloat & first, const iefloat & second);
iefloat subFloats(const iefloat & first, const iefloat & second);
iefloat mulFloats(const iefloat & first, const iefloat & second);

#endif
