#ifndef SPEED_FUNCTIONS__H__
#define SPEED_FUNCTIONS__H__
#include <vector>
#include <array>

typedef std::array<int,2> i2;
typedef std::vector<i2> ps2d;

int sillyAdd(int a, int b);
ps2d drawBresenham(const i2 & start,const i2 & end);

#endif
