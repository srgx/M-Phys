#include "vectors_functions.h"
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

using std::vector;

// Add vectors
vector<float> addVectors(const vector<float> & v1, const vector<float> & v2){

  // Vectors must be the same size
  if(v1.size()!=v2.size()){

    // If vectors are of different sizes, return empty list
    return {};

  }else{

    vector<float> vec;

    // Add corresponding components together
    for(int i=0;i<v1.size();i++){
      vec.push_back(v1.at(i)+v2.at(i));
    }

    return vec;

  }
}

// Subtract vectors
vector<float> subVectors(const vector<float> & v1, const vector<float> & v2){
  return addVectors(v1,oppositeVector(v2));
}


vector<float> scaleVector(const vector<float> & vec, float scale){

  vector<float> nVec;

  //Scale all vector components
  for(int i=0;i<vec.size();i++){
    nVec.push_back(vec.at(i) * scale);
  }

  return nVec;

}

// Length of vector
float magnitude(const vector<float> & vec){

  float s = 0;

  // Sum squares of all components
  for(int i=0;i<vec.size();i++){
    s += pow(vec.at(i),2);
  }

  return sqrt(s);

}

// Normalize vector (create unit vector)
vector<float> norm(const vector<float> & vec){

  float m = magnitude(vec);

  if(m==0){
    // You cant normalize zero vector
    return {};
  }else{
    return scaleVector(vec,1/m);
  }

}

vector<float> normalVector(const vector<float> & vec){
  return vector<float>({ vec.at(1), -vec.at(0) });
}

// Angle between two vectors
float angleBetween(const vector<float> & v1, const vector<float> & v2){

  vector<float> v3 = subVectors(v1,v2);
  float m1 = magnitude(v1);
  float m2 = magnitude(v2);
  float m3 = magnitude(v3);

  // Zero vector or vectors are equal
  if((0==m1||0==m2)||0==m3){

    return 0;

  }else{

    // Calculate angle from cosine rule
    return acos((pow(m1,2) + pow(m2,2) - pow(m3,2))/(2*m1*m2));

  }

}

vector<float> oppositeVector(const vector<float> & vec){

  vector<float> vctr;

  for(auto i=vec.begin();i!=vec.end();i++){
    vctr.push_back(-(*i));
  }

  return vctr;

}

float determinant(const vector<vector<float>> & array){

  int size = array.size();

  if(1==size){

    return array.at(0).at(0);

  }else{

    int mult = 1; float sum = 0;

    // Loop through first row
    for(int i=0;i<size;i++){

      // Value from top row
      float el = array.at(0).at(i);

      // New matrix consists of remaining rows
      // without values at current index (i).
      vector<vector<float>> newmatrix;
      for(int j=1;j<size;j++){
       vector<float> row = array.at(j);
       row.erase(row.begin()+i);
       newmatrix.push_back(row);
      }

      // Array

      // A B C
      // D E F
      // G H I

      // New matrix at A
      // E F
      // H I

      // New matrix at B
      // D F
      // G I

      // New matrix at C
      // D E
      // G H

      // Add current value to sum
      sum += mult*el*determinant(newmatrix);

      // Change sign in every iteration
      mult *= -1;

    }

    return sum;

  }

}

std::array<vector<float>,4> constructSquare(const vector<float> & a, const vector<float> & b){

  std::array<vector<float>,4> result;

  // A
  result.at(0) = a;

  // B
  result.at(1) = b;

  // Vector B->A
  auto firstSide = subVectors(a,b);

  // Vector A->C
  auto secondSide = normalVector(firstSide);

  // C
  result.at(2) = addVectors(a,secondSide);

  // D
  result.at(3) = addVectors(b,secondSide);


  return result;
}

std::array<vector<float>,3> constructEquilateralTriangle(const vector<float> & a, const vector<float> & b){

  std::array<vector<float>,3> result;

  // A
  result.at(0) = a;

  // B
  result.at(1) = b;

  // Vector to middle of AB side
  auto midPoint = addVectors(a,b);
  midPoint = scaleVector(midPoint,1.0/2);

  // Side AB
  auto bottomVector = subVectors(a,b);

  // Perpendicular to AB
  auto heightVector = normalVector(bottomVector);
  heightVector = scaleVector(heightVector,sqrt(3)/2);

  // C
  result.at(2) = addVectors(midPoint,heightVector);

  return result;
}

// Draw letter A. Parameters 3-7 should be in range 0-1
void createA(float legLength, float angleAtTop, float serifProp,
             float crossbarProp, float crossbarHeight, float serifAlign,
             float crossbarAlign){
  
  // Starting position
  vector<float> start { 450, 50 };
  
  
  // Legs
  
    float halfAngle = angleAtTop/2;

    // Left leg vector
    vector<float> leftLeg { -sin(halfAngle), cos(halfAngle) };
    leftLeg = scaleVector(leftLeg,legLength);

    // Right leg vector
    vector<float> rightLeg { -leftLeg.at(0), leftLeg.at(1) };
    
    // Absolute leg positions
    auto leftLegTarget = addVectors(start,leftLeg);
    auto rightLegTarget = addVectors(start,rightLeg);
  
  
  // Crossbar
  
    // Vectors to crossbar points (max width)
    vector<float> crossbarStart = scaleVector(leftLeg,crossbarHeight);
    vector<float> crossbarEnd = scaleVector(rightLeg,crossbarHeight);
    
    // Crossbar vector left->right (max width)
    vector<float> crossbar =
      scaleVector(subVectors(crossbarEnd,crossbarStart),
                  crossbarProp);
    
    // Add vector to align crossbar start
    crossbarStart = addVectors(
      scaleVector(subVectors(crossbarEnd,crossbarStart),crossbarAlign*(1-crossbarProp)),
      crossbarStart);
    
    // Start drawing crossbar from there
    const auto crossbarStartTarget = addVectors(start,crossbarStart);
    
    // Crossbar end position
    auto crossbarEndTarget = addVectors(crossbarStartTarget,crossbar);
  
  
  // Serif

    // Serif vector
    vector<float> serif = scaleVector(subVectors(rightLeg,leftLeg),serifProp);
    
    // Serif offset
    vector<float> serifOffset = scaleVector(serif,serifAlign);
    
    // Left serif
    auto leftSerifBeg = subVectors(leftLegTarget,serifOffset);
    auto leftSerifEnd = addVectors(leftSerifBeg,serif);
    
    // Right serif
    auto rightSerifBeg = subVectors(rightLegTarget,serifOffset);
    auto rightSerifEnd = addVectors(rightSerifBeg,serif);
  
  
  // ---------------------------------------------------------------------------
    
  // Create lines

  sf::Vertex leftLegLine[] = {
    sf::Vertex(sf::Vector2f(start.at(0), start.at(1))),
    sf::Vertex(sf::Vector2f(leftLegTarget.at(0), leftLegTarget.at(1)))
  };

  sf::Vertex rightLegLine[] = {
    sf::Vertex(sf::Vector2f(start.at(0), start.at(1))),
    sf::Vertex(sf::Vector2f(rightLegTarget.at(0), rightLegTarget.at(1)))
  };
  
  sf::Vertex crossbarLine[] = {
    sf::Vertex(sf::Vector2f(crossbarStartTarget.at(0), crossbarStartTarget.at(1))),
    sf::Vertex(sf::Vector2f(crossbarEndTarget.at(0), crossbarEndTarget.at(1))),
  };
  
  sf::Vertex leftSerifLine[] = {
    sf::Vertex(sf::Vector2f(leftSerifBeg.at(0), leftSerifBeg.at(1))),
    sf::Vertex(sf::Vector2f(leftSerifEnd.at(0), leftSerifEnd.at(1))),
  };

  sf::Vertex rightSerifLine[] = {
    sf::Vertex(sf::Vector2f(rightSerifBeg.at(0), rightSerifBeg.at(1))),
    sf::Vertex(sf::Vector2f(rightSerifEnd.at(0), rightSerifEnd.at(1))),
  };

  // ---------------------------------------------------------------------------
  

  sf::RenderWindow wnd(sf::VideoMode(1024, 768), "Letters", sf::Style::Close);
  wnd.setFramerateLimit(30);

  const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while(wnd.isOpen()){

    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;

    while (timeSinceLastUpdate > TimePerFrame){

      timeSinceLastUpdate -= TimePerFrame;

      // Process input
      sf::Event event;
      while(wnd.pollEvent(event)){

        switch (event.type){

          case sf::Event::KeyPressed:

            if(event.key.code == sf::Keyboard::Escape){
                wnd.close();
            }
            break;

          case sf::Event::Closed:

            wnd.close();
            break;

        }

      }


    }


    wnd.clear();

    wnd.draw(leftLegLine, 2, sf::Lines);
    wnd.draw(rightLegLine, 2, sf::Lines);
    wnd.draw(crossbarLine, 2, sf::Lines);
    wnd.draw(leftSerifLine, 2, sf::Lines);
    wnd.draw(rightSerifLine, 2, sf::Lines);

    wnd.display();

  }

}
