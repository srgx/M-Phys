#include <iostream>
#include <cassert>
#include "../Programs/arithmetic_functions.h"

int main(){

  const float MARKER_HEIGHT = 12.5;
  const float TEXT_HEIGHT = 200; const float WINDOW_HEIGHT = 50;
  const float MAX_TEXT_POSITION = TEXT_HEIGHT - WINDOW_HEIGHT;
  const float MAX_MARKER_POSITION = WINDOW_HEIGHT - MARKER_HEIGHT;

  assert(calculateMarkerHeight(TEXT_HEIGHT,WINDOW_HEIGHT) == MARKER_HEIGHT);

  // Top
  assert(calculateMarkerPosition(0,TEXT_HEIGHT,WINDOW_HEIGHT) == 0);
  assert(calculateTextPosition(0,TEXT_HEIGHT,WINDOW_HEIGHT) == 0);

  // Real Middle
  assert(calculateMarkerPosition(TEXT_HEIGHT/2 - WINDOW_HEIGHT/2,
                                 TEXT_HEIGHT,
                                 WINDOW_HEIGHT) ==
         WINDOW_HEIGHT/2 - MARKER_HEIGHT/2);
  assert(calculateTextPosition(WINDOW_HEIGHT/2 - MARKER_HEIGHT/2,
                               TEXT_HEIGHT,
                               WINDOW_HEIGHT) ==
         TEXT_HEIGHT/2 - WINDOW_HEIGHT/2);

  // Middle
  assert(calculateMarkerPosition(TEXT_HEIGHT/2,TEXT_HEIGHT,WINDOW_HEIGHT) ==
         WINDOW_HEIGHT/2);
  assert(calculateTextPosition(WINDOW_HEIGHT/2,TEXT_HEIGHT,WINDOW_HEIGHT) ==
         TEXT_HEIGHT/2);

  // Bottom
  assert(calculateMarkerPosition(MAX_TEXT_POSITION,TEXT_HEIGHT,WINDOW_HEIGHT) ==
         MAX_MARKER_POSITION);
  assert(calculateTextPosition(MAX_MARKER_POSITION,TEXT_HEIGHT,WINDOW_HEIGHT) ==
         MAX_TEXT_POSITION);

  std::cout << "Part 1 - Chapter 2 - Exercise 1\n";

}
