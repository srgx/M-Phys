#ifndef VECTORS_FUNCTIONS__H__
#define VECTORS_FUNCTIONS__H__
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>



struct basis {
  std::vector<double> b1;
  std::vector<double> b2;
  double a;
  double b;
};

std::vector<double> addVectors(const std::vector<double> & v1, const std::vector<double> & v2);
std::vector<double> subVectors(const std::vector<double> & v1, const std::vector<double> & v2);
std::vector<double> scaleVector(const std::vector<double> & vec, double scale);
double magnitude(const std::vector<double> & vec);
std::vector<double> norm(const std::vector<double> & vec);
std::vector<double> normalVector(const std::vector<double> & vec);
double angleBetween(const std::vector<double> & v1, const std::vector<double> & v2);
std::vector<double> oppositeVector(const std::vector<double> & vec);
double determinant(const std::vector<std::vector<double>> & array);

std::array<std::vector<double>,4> constructSquare(const std::vector<double> & a, const std::vector<double> & b);
std::array<std::vector<double>,3> constructEquilateralTriangle(const std::vector<double> & a, const std::vector<double> & b);
void createA(double legLength, double angleAtTop, double serifProp,
             double crossbarProp, double crossbarHeight, double serifAlign,
             double crossbarAlign);


void renderLines(const std::vector<std::array<sf::Vertex,2>> & lines);

std::vector<double> curvedPath(const std::vector<double> & endPoint,
                const std::vector<double> & currentPoint, double speed,
                double normalProportion, double timeStep);


void drawCurvedPath(const std::vector<double> & endPoint,
                    const std::vector<double> & currentPoint, double speed,
                    double normalProportion, double timeStep);


std::pair<std::vector<double>,double>
  madPath(const std::vector<double> & endPoint,
          const std::vector<double> & currentPoint,
          double currentAlpha,
          double speed,
          double alphaSpeed,
          double timeStep);
  

void drawMadPath(const std::vector<double> & endPoint,
                 const std::vector<double> & currentPoint,
                 double currentAlpha,
                 double speed,
                 double alphaSpeed,
                 double timeStep);


basis switchBasis(const std::vector<double> & vec,
                  const std::vector<double> & directionVec);


double component(const std::vector<double> & vec,
                const std::vector<double> & directionVec);


std::vector<double> componentVector(const std::vector<double> & vec,
                                    const std::vector<double> & directionVec);


std::vector<double> intersectionPoint(const std::vector<double> & a,
                                      const std::vector<double> & b,
                                      const std::vector<double> & c,
                                      const std::vector<double> & d);



double intersectionTime(std::vector<double> p1,
                        std::vector<double> v1,
                        std::vector<double> p2,
                        std::vector<double> v2);


double intersection(const std::vector<double> & a,
                    const std::vector<double> & b,
                    const std::vector<double> & c,
                    const std::vector<double> & d);


void drawArrowhead(double lineSegment,double size, double angle);

void drawKite(double lineSegment, double height, double width, double angle);

void drawShape(int index);

void drawCube(double side, double angle, double depth);

#endif
