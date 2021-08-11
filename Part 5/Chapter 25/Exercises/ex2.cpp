#include <iostream>
#include <ctime>
#include <cstdlib>
#include <array>
#include <SFML/Graphics.hpp>

const int numBoids = 100;
const int verPosRange = 500;
const int horPosRange = 900;
const int velRange = 2;
const int boidRadius = 2;
const int massCenterRadius = 6;

using std::array;
using std::cout;

typedef array<float,2> vec2d;

enum Type {Velocity,Mass};

class Boid{
public:
  vec2d position;
  vec2d velocity;
  sf::CircleShape shape;
  void showPosition() const;
  void showVelocity() const;
  void draw(sf::RenderWindow & w) const;
  void move();
  Boid();
};

void showVec(const vec2d & vec);
vec2d findAverageBoid(const array<Boid,numBoids> & boids,Type t);
vec2d findMassCenter(const array<Boid,numBoids> & boids);
vec2d findAverageVelocity(const array<Boid,numBoids> & boids);

// g++ -c ex2.cpp && g++ ex2.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system && ./a.out

int main(){

  sf::CircleShape mCenter(massCenterRadius);
  mCenter.setOrigin(massCenterRadius,massCenterRadius);
  mCenter.setFillColor(sf::Color::Green);

  srand(time(0));

  array<Boid,numBoids> boids;

  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Flocking Boids");
  window.setFramerateLimit(30);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) { window.close(); }
    }


    // Calculations
    vec2d massCenter = findMassCenter(boids);
    vec2d averageVelocity = findAverageVelocity(boids);


    // Mass center position
    mCenter.setPosition(massCenter[0],massCenter[1]);

    // Move boids
    for(Boid & b : boids){ b.move(); }

    window.clear();

    // Draw all objects
    for(const Boid & b : boids){ b.draw(window); }
    window.draw(mCenter);

    window.display();

  }

}

void Boid::showPosition() const{
  showVec(position);
}

void Boid::showVelocity() const{
  showVec(velocity);
}

void Boid::draw(sf::RenderWindow & w) const{
  w.draw(shape);
}

void Boid::move(){
  for(int i=0;i<2;i++){
    position[i] += velocity[i];
  }
  shape.setPosition(position[0],position[1]);
}

Boid::Boid(){

  // Initialize boid data
  for(int j=0;j<2;j++){
    position[j] = rand() % (0 == j ? horPosRange : verPosRange);
    velocity[j] = rand() % velRange;
  }

  // Create boid shape
  shape = sf::CircleShape(boidRadius);
  shape.setOrigin(boidRadius,boidRadius);
  shape.setPosition(position[0],position[1]);
  shape.setFillColor(sf::Color::Red);

}

void showVec(const vec2d & vec){
  cout << vec[0] << ", " << vec[1] <<  '\n';
}

vec2d findMassCenter(const array<Boid,numBoids> & boids){
  return findAverageBoid(boids,Type::Mass);
}

vec2d findAverageVelocity(const array<Boid,numBoids> & boids){
  return findAverageBoid(boids,Type::Velocity);
}

vec2d findAverageBoid(const array<Boid,numBoids> & boids,Type t){

  const int s = 2;
  vec2d averageVec = {0,0};

  switch(t){

    case Type::Velocity:
      for(const Boid & b : boids){ for(int i=0;i<s;i++){ averageVec[i] += b.velocity[i]; } }
    break;

    case Type::Mass:
      for(const Boid & b : boids){ for(int i=0;i<s;i++){ averageVec[i] += b.position[i]; } }
    break;

    default:
      break;
  }

  for(int i=0;i<s;i++){ averageVec[i] /= numBoids; }

  return averageVec;

}
