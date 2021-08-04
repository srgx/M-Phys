#include <iostream>
#include <algorithm>
#include <random>
#include "maze_functions.h"

Maze::Maze(int wdth, int hght) : width(wdth), height(hght) {

  for (int i=0;i<height;i++){
    std::vector<MazeCell> row;
    for (int j=0;j<width;j++){
      row.push_back(MazeCell());
    }
    cells.push_back(row);
  }

}

void Maze::showMaze() const{
  for (const auto & row : cells){
    for (const auto & c : row) {
      c.showCell();
    }
    std::cout << '\n';
  }
}

MazeCell::MazeCell() : northWall(true), eastWall(true) {
}

void MazeCell::showCell() const{
  using std::cout;
  cout << (northWall ? 'N' : ' ');
  cout << (eastWall ? 'E' : ' ');
  cout << ' ';
}

void recursiveBacktrack(Maze & maze,
                        cell startCell,
                        cell endCell,
                        std::vector<cell> & path){

  if (path.empty()) { path.push_back(startCell); }

  cell currentCell = path.back();

  std::vector<cell> neighbours =
    getNeighbours(maze.width,maze.height,currentCell);


  std::random_device rd;
  auto reng = std::default_random_engine { rd() };
  std::shuffle(std::begin(neighbours), std::end(neighbours), reng);

  for (const auto & c : neighbours) {

    std::cout << c[0] << ", " << c[1] << '\n';

    if (!std::count(path.begin(), path.end(), c)) {

      std::cout << "Element not found\n";

      path.push_back(c);

      // remove wall

      recursiveBacktrack(maze,startCell,endCell,path);

    } else {
      std::cout << "Element found\n";
    }

  }

}

std::vector<cell> getNeighbours(int width, int height,const cell & c){

  std::vector<cell> result;

  int col = c[0]; int row = c[1]; int nextCell = col - 1;

  // Left
  if (nextCell >= 0) { result.push_back({nextCell,row}); }

  // Right
  nextCell = col + 1;
  if (nextCell < width) { result.push_back({nextCell,row}); }

  // Top
  nextCell = row - 1;
  if (nextCell >= 0) { result.push_back({col,nextCell}); }

  // Bot
  nextCell = row + 1;
  if (nextCell<height) { result.push_back({col,nextCell}); }

  return result;

}
