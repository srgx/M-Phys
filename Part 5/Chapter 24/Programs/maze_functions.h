#ifndef MAZE_FUNCTIONS__H__
#define MAZE_FUNCTIONS__H__
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>


using std::vector;

enum Side {North,East};
typedef std::array<int,2> cell;
const int prop = 20;
const int lineWidth = 2;

struct MazeCell {
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

struct Maze {
  int width;
  int height;
  sf::RectangleShape leftWall;
  sf::RectangleShape botWall;
  vector<vector<MazeCell>> cells;
  Maze(int wdth, int hght);
  void showMaze() const;
  void removeWall(const cell & c, Side s);
  void drawMaze(sf::RenderWindow & w) const;
};

struct KruskalCell {
  int id;
  cell c;
  KruskalCell(const cell & ce);
};

struct KruskalMaze {
  vector<cell> walls;
  vector<KruskalCell> cells;
  int width;
  int height;
  KruskalMaze(int wdth,int hght);
};


void recursiveBacktrack(Maze & maze,cell startCell,cell endCell,
                        vector<cell> & path);
vector<cell> getNeighbours(int width, int height,const cell & c);

void kruskal(KruskalMaze & maze);

#endif
