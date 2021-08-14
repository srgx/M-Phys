#include <iostream>
#include <algorithm>
#include <random>
#include "maze_functions.h"

using std::cout;

Maze::Maze(int wdth, int hght) : width(wdth), height(hght) {

  for (int i=0;i<height;i++){
    std::vector<MazeCell> row;
    for (int j=0;j<width;j++){
      cell pos = {j,i};
      row.push_back(MazeCell(pos));
    }
    cells.push_back(row);
  }

  leftWall.setSize(sf::Vector2f(lineWidth, prop*height));
  leftWall.setFillColor(sf::Color::Red);

  botWall.setSize(sf::Vector2f(prop*height,lineWidth));
  botWall.setFillColor(sf::Color::Red);
  botWall.setPosition(0, prop*height);

}

void Maze::showMaze() const{
  for (const auto & row : cells){
    for (const auto & c : row) {
      c.showCell();
    }
    cout << '\n';
  }
}

void Maze::removeWall(const cell & c, Side s){

  int x = c[0]; int y = c[1];

  switch(s){

    case Side::North:
      cells[y][x].removeNorthWall();
      break;

    case Side::East:
      cells[y][x].removeEastWall();
      break;

    default:
      break;

  }

}

void Maze::drawMaze(sf::RenderWindow & w) const{

  w.draw(leftWall);
  w.draw(botWall);

  for(int y=0;y<height;y++){
    for(int x=0;x<width;x++){
      cell pos = {x,y};
      cells[y][x].drawCell(w);
    }
  }

}

MazeCell::MazeCell(const cell & c) : northWall(true), eastWall(true) {

  northRect.setSize(sf::Vector2f(prop, lineWidth));
  northRect.setFillColor(sf::Color::Red);
  northRect.setPosition(c[0]*prop, c[1]*prop);

  eastRect.setSize(sf::Vector2f(lineWidth, prop));
  eastRect.setFillColor(sf::Color::Red);
  eastRect.setPosition(c[0]*prop+prop, c[1]*prop);
}

void MazeCell::showCell() const{
  cout << (northWall ? 'N' : ' ');
  cout << (eastWall ? 'E' : ' ');
  cout << ' ';
}

void MazeCell::removeNorthWall(){
  northWall = false;
}

void MazeCell::removeEastWall(){
  eastWall = false;
}

void MazeCell::drawCell(sf::RenderWindow & w) const{
  if(northWall){ w.draw(northRect); }
  if(eastWall){ w.draw(eastRect); }
}

KruskalMaze::KruskalMaze(int wdth,int hght) : width(wdth), height(hght){

  // Create cells and walls
  for(int y=0;y<height;y++){
    for(int x=0;x<width;x++){
      cells.push_back(KruskalCell({x,y}));
      if(x<width-1 && y<height-1){
        walls.push_back({x,y});
      }
    }
  }

}

KruskalCell::KruskalCell(const cell & ce) : c(ce){
}

// ------------------------------------------------------------------

void recursiveBacktrack(Maze & maze,cell startCell,cell endCell,
                        std::vector<cell> & path){

  if (path.empty()) { path.push_back(startCell); }

  cell currentCell = path.back();

  std::vector<cell> neighbours =
    getNeighbours(maze.width,maze.height,currentCell);


  std::random_device rd;
  auto reng = std::default_random_engine { rd() };
  std::shuffle(std::begin(neighbours), std::end(neighbours), reng);

  for (const auto & neighbour : neighbours) {

    cout << neighbour[0] << ", " << neighbour[1] << '\n';

    if (!std::count(path.begin(), path.end(), neighbour)) {

      cout << "Element not found\n";

      path.push_back(neighbour);

      // Remove walls

      // West
      if(neighbour==cell({currentCell[0]-1,currentCell[1]})){
        maze.removeWall(neighbour,Side::East);

      // East
      } else if(neighbour==cell({currentCell[0]+1,currentCell[1]})){
        maze.removeWall(currentCell,Side::East);

      // North
      } else if(neighbour==cell({currentCell[0],currentCell[1]-1})){
        maze.removeWall(currentCell,Side::North);

      // South
      } else if(neighbour==cell({currentCell[0],currentCell[1]+1})){
        maze.removeWall(neighbour,Side::North);

      } else {
        cout << "Error\n";
      }

      recursiveBacktrack(maze,startCell,endCell,path);

    } else {
      cout << "Element found\n";
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

void kruskal(KruskalMaze & maze){

  std::vector<cell> wallList = maze.walls;

  std::random_device rd;
  auto reng = std::default_random_engine { rd() };
  std::shuffle(std::begin(wallList), std::end(wallList), reng);

  int i = 0;
  for(int y=0;y<maze.height;y++){
    for(int x=0;x<maze.width;x++){
      maze.cells[i].id = i++;
    }
  }

}
