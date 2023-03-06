#include <iostream>
#include <ctime>
#include <cstdlib>
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

const int numBoids = 100;
const int verPosRange = 500;
const int horPosRange = 900;
const int velRange = 5;
const int boidRadius = 2;
const int massCenterRadius = 5;

using std::array;
using std::cout;

typedef array<float,2> vec2d;

enum Type {Velocity,Mass};

struct Boid{
  vec2d position;
  vec2d velocity;
  sf::CircleShape shape;
  void showPosition() const;
  void showVelocity() const;
  void draw(sf::RenderWindow & w) const;
  void move();
  vec2d getUpdatedVelocityTowardPoint(const vec2d & point) const;
  vec2d getUpdatedVelocityTowardAverageVelocity(const vec2d & averageVelocity) const;
  Boid();
};

void showVec(const vec2d & vec);
vec2d findAverageBoid(const array<Boid,numBoids> & boids,Type t);
vec2d findMassCenter(const array<Boid,numBoids> & boids);
vec2d findAverageVelocity(const array<Boid,numBoids> & boids);
vec2d subVector(const vec2d & a,const vec2d & b);
vec2d addVector(const vec2d & a,const vec2d & b);
vec2d unitVector(const vec2d & ve);
float magnitude(const vec2d & ve);
vec2d divVector(const vec2d & vec,float num);
vec2d mulVector(const vec2d & vec,float num);


// g++ -c ex2.cpp && g++ ex2.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system && ./a.out

int main(){

  // Initialize mass center shape
  sf::CircleShape mCenter(massCenterRadius);
  mCenter.setOrigin(massCenterRadius,massCenterRadius);
  mCenter.setFillColor(sf::Color::Green);

  srand(time(0));

  // Initialize boids
  // Their position and speed are
  // randomly set in the constructor
  array<Boid,numBoids> boids;

  // Create main window
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

    // -------------------------------------------------------------

    // Velocities to mass center
    array<vec2d,numBoids> velocitiesToMassCenter;
    for(int i=0;i<numBoids;i++){
      velocitiesToMassCenter[i] = boids[i].getUpdatedVelocityTowardPoint(massCenter);
    }

    // Velocities to average velocity
//     array<vec2d,numBoids> velocitiesToAverageVelocity;
//     for(int i=0;i<numBoids;i++){
//       velocitiesToAverageVelocity[i] =
//         boids[i].getUpdatedVelocityTowardAverageVelocity(averageVelocity);
//     }

    // -------------------------------------------------------------

    // Update boid velocities
    for(int i=0;i<numBoids;i++){
//       boids[i].velocity =
//         divVector(addVector(velocitiesToAverageVelocity[i],
//                             velocitiesTowardPoint[i]),
//                   2
//                  );
      boids[i].velocity = velocitiesToMassCenter[i];
    }


    // Move boids
    for(Boid & b : boids){ b.move(); }

    window.clear();

    // Draw all boids
    for(const Boid & b : boids){ b.draw(window); }

    // Draw mass center
    window.draw(mCenter);

    window.display();

  }

  std::cout << "Part 5 - Chapter 25 - Exercise 2\n";

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

// Update boid position
void Boid::move(){
  for(int i=0;i<2;i++){
    position[i] += velocity[i];
  }
  shape.setPosition(position[0],position[1]);
}

// Acceleration decreases as the boid approaches the target
vec2d Boid::getUpdatedVelocityTowardPoint(const vec2d & point) const {
  return addVector(velocity,divVector(subVector(point,position),1e3));
}

// Boid tries to move at average speed
vec2d Boid::getUpdatedVelocityTowardAverageVelocity(const vec2d & averageVelocity) const{
  vec2d accelerationVector = divVector(subVector(averageVelocity,velocity),2);
  return addVector(velocity,accelerationVector);
}

Boid::Boid(){

  // Initialize boid data
  for(int j=0;j<2;j++){
    position[j] = rand() % (0 == j ? horPosRange : verPosRange);
    velocity[j] = rand() % velRange - 2;
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


// The centre of mass is the average boid position
vec2d findMassCenter(const array<Boid,numBoids> & boids){
  return findAverageBoid(boids,Type::Mass);
}


// Average boid velocity
vec2d findAverageVelocity(const array<Boid,numBoids> & boids){
  return findAverageBoid(boids,Type::Velocity);
}


// Helper function
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

vec2d subVector(const vec2d & a,const vec2d & b){
  return {a[0]-b[0],a[1]-b[1]};
}

vec2d addVector(const vec2d & a,const vec2d & b){
  return {a[0]+b[0],a[1]+b[1]};
}

vec2d divVector(const vec2d & vec,float num){
  return {vec[0]/num,vec[1]/num};
}

vec2d mulVector(const vec2d & vec,float num){
  return {vec[0]*num,vec[1]*num};
}

vec2d unitVector(const vec2d & ve){
  float mag = magnitude(ve);
  return 0 == mag ? vec2d({0,0}) : divVector(ve,mag);
}

float magnitude(const vec2d & ve){
  return sqrt(pow(ve[0],2)+pow(ve[1],2));
}
