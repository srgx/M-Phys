#ifndef VECTORS_FUNCTIONS__H__
#define VECTORS_FUNCTIONS__H__
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>



struct basis {
  std::vector<float> b1;
  std::vector<float> b2;
  float a;
  float b;
};

std::vector<float> addVectors(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> subVectors(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> scaleVector(const std::vector<float> & vec, float scale);
float magnitude(const std::vector<float> & vec);
std::vector<float> norm(const std::vector<float> & vec);
std::vector<float> normalVector(const std::vector<float> & vec);
float angleBetween(const std::vector<float> & v1, const std::vector<float> & v2);
std::vector<float> oppositeVector(const std::vector<float> & vec);
float determinant(const std::vector<std::vector<float>> & array);

std::array<std::vector<float>,4> constructSquare(const std::vector<float> & a, const std::vector<float> & b);
std::array<std::vector<float>,3> constructEquilateralTriangle(const std::vector<float> & a, const std::vector<float> & b);
void createA(float legLength, float angleAtTop, float serifProp,
             float crossbarProp, float crossbarHeight, float serifAlign,
             float crossbarAlign);


void renderLines(const std::vector<std::array<sf::Vertex,2>> & lines);

std::vector<float> curvedPath(const std::vector<float> & endPoint,
                const std::vector<float> & currentPoint, float speed,
                float normalProportion, float timeStep);


void drawCurvedPath(const std::vector<float> & endPoint,
                    const std::vector<float> & currentPoint, float speed,
                    float normalProportion, float timeStep);


std::pair<std::vector<float>,float>
  madPath(const std::vector<float> & endPoint,
          const std::vector<float> & currentPoint,
          float currentAlpha,
          float speed,
          float alphaSpeed,
          float timeStep);
  

void drawMadPath(const std::vector<float> & endPoint,
                 const std::vector<float> & currentPoint,
                 float currentAlpha,
                 float speed,
                 float alphaSpeed,
                 float timeStep);


basis switchBasis(const std::vector<float> & vec,
                  const std::vector<float> & directionVec);


float component(const std::vector<float> & vec,
                const std::vector<float> & directionVec);


std::vector<float> componentVector(const std::vector<float> & vec,
                                   const std::vector<float> & directionVec);


std::vector<float> intersectionPoint(const std::vector<float> & a,
                                     const std::vector<float> & b,
                                     const std::vector<float> & c,
                                     const std::vector<float> & d);

#endif
