#ifndef MAZE_FUNCTIONS__H__
#define MAZE_FUNCTIONS__H__
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>


enum Side {North,East};
typedef std::array<int,2> cell;
const int prop = 20;
const int lineWidth = 2;

class MazeCell {
public:
  bool northWall;
  bool eastWall;
  sf::RectangleShape northRect;
  sf::RectangleShape eastRect;
  MazeCell(const cell & c);
  void showCell() const;
  void removeNorthWall();
  void removeEastWall();
  void drawCell(sf::RenderWindow & w) const;
};

class Maze {
public:
  int width;
  int height;
  sf::RectangleShape leftWall;
  sf::RectangleShape botWall;
  std::vector<std::vector<MazeCell>> cells;
  Maze(int wdth, int hght);
  void showMaze() const;
  void removeWall(const cell & c, Side s);
  void drawMaze(sf::RenderWindow & w) const;
};


void recursiveBacktrack(Maze & maze,cell startCell,cell endCell,
                        std::vector<cell> & path);
std::vector<cell> getNeighbours(int width, int height,const cell & c);

#endif
