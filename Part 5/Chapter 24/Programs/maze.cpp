#include <iostream>
#include "maze_functions.h"

using std::cout;

int main(){

  std::vector<cell> path;
  Maze maze(5,5);

  maze.showMaze();

  //recursiveBacktrack(maze,{2,2},{4,4},path);

  cout << "Part 5 - Chapter 24 - Maze\n";

}
