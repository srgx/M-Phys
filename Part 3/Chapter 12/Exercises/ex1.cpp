#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "../Programs/force_functions.h"

// g++ -c ex1.cpp ../Programs/force_functions.cpp && g++ ex1.o force_functions.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system && ./a.out

using std::cout;
using std::endl;

class planet{
public:
  double mass;
  v2d velocity;
  v2d position;
  std::vector<v2d> positions;
  sf::CircleShape shape;
  planet(double m, const v2d & vel,const v2d & pos,double radius,sf::Color color);
  void updateShapePosition(int i);
  void draw(sf::RenderWindow & w);
};


v2d getGravityVector(const planet & currentPlanet, const planet & otherPlanet);

int main(){

  const double scale = 5e6;
  const int offsetX = 450;
  const int offsetY = 250;
  const int steps = 2419200*3;

  planet planetEarth(earthMass,{0,0},{0,0}, 20, sf::Color::Cyan);
  planetEarth.shape.setPosition(offsetX,offsetY);

  std::array<planet,3> planets =
    { planet(moonMass,{-1024,0},{0,-3844e5}, 5, sf::Color::Magenta),
      planet(2.93908e22, {1435,0}, {0,1.922e8}, 3, sf::Color::Red),
      planet(moonMass*1.2, {760,0}, {0,6.9192e8}, 10, sf::Color::Yellow)
    };


  int i = 0;
  for(int i=0;i<steps;i++){

    // Calculate velocity for all planets
    for(int j=0;j<planets.size();j++){

      // Calculate total gravity force
      v2d totalGravity = getGravityVector(planets[j],planetEarth);

      for(int k=0;k<planets.size();k++){
        if(k!=j){
          totalGravity = addVectors(totalGravity,
                                    getGravityVector(planets[j],planets[k]));
        }
      }

      // Add acceleration to get new velocity
      planets[j].velocity = addVectors(planets[j].velocity,
                                       divVector(totalGravity,planets[j].mass));

    }

    // Update positions with new velocity
    for(int j=0;j<planets.size();j++){
      planets[j].position = addVectors(planets[j].position,planets[j].velocity);
    }

    // Save some positions to play animation
    if (i % 5000 == 0) {
      for(int j=0;j<planets.size();j++){
        planets[j].positions.push_back({planets[j].position[0]/scale+offsetX,
                                        planets[j].position[1]/scale+offsetY});
      }
    }

  }

  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Planets");
  window.setFramerateLimit(30);

  i = 0;
  while (window.isOpen()){

    i++;
    if (i >= planets[0].positions.size()){
      window.close();
    } else {
      for(int j=0;j<planets.size();j++){
        planets[j].updateShapePosition(i);
      }
    }

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) { window.close(); }
    }

    window.clear();
    planetEarth.draw(window);
    for(int j=0;j<planets.size();j++){ planets[j].draw(window); }
    window.display();

  }

}

v2d getGravityVector(const planet & currentPlanet, const planet & otherPlanet){
  return mulVector(unitVector(subVectors(otherPlanet.position,
                                         currentPlanet.position)),
                   gravityForce(otherPlanet.mass,
                                currentPlanet.mass,
                                distance(currentPlanet.position,
                                         otherPlanet.position)));
}

planet::planet(double m,const v2d & vel,const v2d & pos,double radius,sf::Color color){
  mass = m;
  velocity = vel;
  position = pos;
  shape = sf::CircleShape(radius);
  shape.setOrigin(radius,radius);
  shape.setFillColor(color);
}

void planet::updateShapePosition(int i){
  shape.setPosition(positions[i][0],positions[i][1]);
}

void planet::draw(sf::RenderWindow & w){
  w.draw(shape);
}
