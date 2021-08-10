#include <iostream>
#include <ctime>
#include <cstdlib>
#include <array>

using std::array;
using std::cout;

typedef array<float,2> vec2d;

class Boid{
public:
  vec2d position;
  vec2d velocity;
  void showPosition() const;
  void showVelocity() const;
  Boid();
};

const int numBoids = 5;
const int posRange = 201;
const int velRange = 3;

int main(){

  srand(time(0));

  array<Boid,numBoids> boids;

  for(const Boid & b : boids){
    b.showPosition();
    b.showVelocity();
  }

  cout << "Flocking Boids\n";

}

void Boid::showPosition() const{
  cout << position[0] << ", " << position[1] << '\n';
}

void Boid::showVelocity() const{
  cout << velocity[0] << ", " << velocity[1] <<  '\n';
}

Boid::Boid(){
  for(int j=0;j<2;j++){
    position[j] = rand() % posRange;
    velocity[j] = rand() % velRange;
  }
}
