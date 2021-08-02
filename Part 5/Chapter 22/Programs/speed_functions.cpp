#include <iostream>
#include "speed_functions.h"

int sillyAdd(int a, int b){
  for (int i=1; i<=a; i++){
    ++b;
  }
  return b;
}

ps2d drawBresenham(const i2 & start, const i2 & end){

  ps2d points = { start };

  int x = start[0]; int y = start[1];
  int a = end[0] - x; int b = end[1] - y;
  int d = 2 * (a + b); int e = 2 * a;

  int lineFn = -2 * a - b;

  for (int xx = x + 1; xx <= end[0]; xx++){

    if (lineFn > 0){ // lineFn < 0 in book
      // Move up
      y--; lineFn -= d;
    } else {
      // Move rights
      lineFn += e;
    }

    points.push_back(i2({xx,y}));

  }

  return points;

}
