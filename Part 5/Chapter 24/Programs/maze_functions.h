#ifndef MAZE_FUNCTIONS__H__
#define MAZE_FUNCTIONS__H__
#include <array>
#include <vector>

class MazeCell {
public:
  bool northWall;
  bool eastWall;
  MazeCell();
  void showCell() const;
};

class Maze {
public:
  int width;
  int height;
  std::vector<std::vector<MazeCell>> cells;
  Maze(int wdth, int hght);
  void showMaze() const;
};

typedef std::array<int,2> cell;

void recursiveBacktrack(Maze & maze,
                        cell startCell,
                        cell endCell,
                        std::vector<cell> & path);

std::vector<cell> getNeighbours(int width, int height,const cell & c);

#endif
