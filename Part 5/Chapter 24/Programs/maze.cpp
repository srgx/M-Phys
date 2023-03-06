#include <iostream>
#include <SFML/Graphics.hpp>
#include "maze_functions.h"

using std::cout;

// g++ -c maze.cpp maze_functions.cpp && g++ maze.o maze_functions.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system && ./a.out

int main(){

  KruskalMaze km(5,5);
  kruskal(km);

  // return 0;

  // ---------------------

  std::vector<cell> path;
  Maze maze(20,20);

  maze.showMaze();

  recursiveBacktrack(maze,{2,2},{15,15},path);

  maze.showMaze();

  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mazes");
  window.setFramerateLimit(30);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) { window.close(); }
    }


    window.clear();

    maze.drawMaze(window);

    window.display();

  }

  cout << "Part 5 - Chapter 24 - Maze\n";

}
