#include <SFML/Graphics.hpp>
#include <array>
#include "../Programs/force_functions.h"

// g++ -c ex1.cpp ../Programs/force_functions.cpp && g++ ex1.o force_functions.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system && ./a.out

int main(){

  const double earthR = 20;
  const double moonR = 5;
  const double scale = 5e6;
  const int offsetX = 400;
  const int offsetY = 150;
  const int steps = 2419200*3;

  v2d earthPosition = {0,0};
  v2d moonPosition = {0,-3844e5};
  v2d moonVelocity = {-1023,0};

  sf::CircleShape earth(earthR);
  earth.setOrigin(earthR,earthR);
  earth.setFillColor(sf::Color::Cyan);
  earth.setPosition(offsetX,offsetY);

  sf::CircleShape moon(moonR);
  moon.setOrigin(moonR,moonR);
  moon.setFillColor(sf::Color::Magenta);

  int i = 0;
  std::vector<v2d> positions;
  for(int i=0; i < steps;i++){

    v2d gravityVector =
      mulVector(unitVector(subVectors(earthPosition,moonPosition)),
                gravityForce(earthMass,moonMass,distance(moonPosition,earthPosition)));

    // Add acceleration to get new velocity
    moonVelocity = addVectors(moonVelocity,divVector(gravityVector,moonMass));

    // Update position with new velocity
    moonPosition = addVectors(moonPosition,moonVelocity);

    if (i % 5000 == 0) {
      positions.push_back({moonPosition[0]/scale+offsetX,moonPosition[1]/scale+offsetY});
    }

  }

  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Planets");
  window.setFramerateLimit(30);

  i = 0;
  while (window.isOpen()){

    i++;
    if (i >= positions.size()){
      window.close();
    } else {
      moon.setPosition(positions[i][0],positions[i][1]);
    }

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) { window.close(); }
    }

    window.clear();
    window.draw(earth);
    window.draw(moon);
    window.display();

  }

}
