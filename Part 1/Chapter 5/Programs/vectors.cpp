#include "vectors_functions.h"
#include <cassert>
#include <cmath>
#include <iostream>

typedef std::vector<double> vecd;

int main(){

  const double mg = sqrt(109);
  const double d = 1e-5;

  // Add Vectors
  assert(addVectors(vecd({ 3, 4 }),
                    vecd({ 7, 16 })) ==
                    vecd({ 10, 20 }));
  assert(addVectors(vecd({ 3, 4 }),
                    vecd({ 0, 0 })) ==
                    vecd({ 3, 4 }));
  assert(addVectors(vecd({ 3, 4, }),
                    vecd({ 7, 16, 22 })) ==
                    vecd());

  // Sub Vectors
  assert(subVectors(vecd({ 3, 4 }),
                    vecd({ 7, 16 })) ==
                    vecd({ -4, -12 }));
  assert(subVectors(vecd({ 3, 4 }),
                    vecd({ 2, 1 })) ==
                    vecd({ 1, 3 }));
  assert(subVectors(vecd({ 3, 4, }),
                    vecd({ 7, 16, 22 })) ==
                    vecd());

  // Scale Vectors
  assert(scaleVector(vecd({ 15, 30 }), 3) ==
                     vecd({ 45, 90 }));
  assert(scaleVector(vecd({ 20 , 10 }), 1.5) ==
                     vecd({ 30, 15 }));
  assert(scaleVector(vecd({ 12 , 22 }), 0) ==
                     vecd({ 0, 0 }));

  // Vector Magnitude
  assert(magnitude(vecd({ 3, 4 })) == 5);
  assert(magnitude(vecd({ 5, 12 })) == 13);
  assert(std::abs(magnitude(vecd({ 3, 6, 8 }))-mg)<d);

  // Normalize Vector
  assert(norm(vecd({ 0, 0 })) == vecd({}));
  vecd vec = norm(vecd({ 3, 4 }));
  assert(std::abs(vec.at(0)-3.0/5)<d);
  assert(std::abs(vec.at(1)-4.0/5)<d);
  vec = norm(vecd({ 5, 12 }));
  assert(std::abs(vec.at(0)-5.0/13)<d);
  assert(std::abs(vec.at(1)-12.0/13)<d);
  vec = norm(vecd({ 3, 6, 8 }));
  assert(std::abs(vec.at(0)-3/mg)<d);
  assert(std::abs(vec.at(1)-6/mg)<d);
  assert(std::abs(vec.at(2)-8/mg)<d);

  // Opposite Vector
  assert(oppositeVector(vecd({ 3, 4 })) ==
                        vecd({ -3, -4}));
  assert(oppositeVector(vecd({ 0, -5 })) ==
                        vecd({ 0, 5}));
  assert(oppositeVector(vecd({ 0, 0 })) ==
                        vecd({ 0, 0}));


  // Vectors Angle
  assert(angleBetween(vecd({ 5, 6 }),
                      vecd({ 5, 6 })) == 0);
  assert(angleBetween(vecd({ 5, 6 }),
                      vecd({ 0, 0 })) == 0);
  assert(std::abs(angleBetween(vecd({ 3, 4 }),
                               vecd({ 4, 3 })) - 0.2838)<d);
  assert(std::abs(angleBetween(vecd({ 5, 0 }),
                               vecd({ 0, 5 })) - M_PI/2)<d);
  assert(std::abs(angleBetween(vecd({ 5, 0 }),
                               vecd({ 5, 5 })) - M_PI/4)<d);


  // Determinant
  std::vector<vecd> mx {
    { 1, 3, 2 },
    { -3, -1, -3 },
    { 2, 3, 1 },
  };
  assert(determinant(mx)==-15);

  mx = std::vector<vecd>({{ 2, -3, 1 },
                          { 2, 0, -1 },
                          { 1, 4, 5 }});
  assert(determinant(mx)==49);

  // Normal vector(perpendicular)
  assert(normalVector(vecd({ 2, 3 })) == vecd({ 3, -2 }));
  assert(normalVector(vecd({ 5, 7 })) == vecd({ 7, -5 }));
  assert(normalVector(vecd({ 4, 0 })) == vecd({ 0, -4 }));
  assert(normalVector(vecd({ 0, 9 })) == vecd({ 9, 0 }));


  // Construct square
  vecd a { 2, 3 }; vecd b { 2, 0 };
  assert(constructSquare(a,b)==(std::array<std::vector<double>,4>({{
    { 2, 3 }, { 2, 0 },
    { 5, 3 }, { 5, 0 }}
  })));

  a = vecd({ 5, 2 }); b = vecd({ 2, 1 });
  assert(constructSquare(a,b)==(std::array<std::vector<double>,4>({{
    { 5, 2 }, { 2, 1 },
    { 6, -1 }, { 3, -2 }}
  })));

  
  // Construct equilateral triangle
  auto trng = constructEquilateralTriangle(vecd({ 2, 2 }), vecd({ 10, 2 }));
  
  assert(std::abs(trng.at(0).at(0)-2)<d);
  assert(std::abs(trng.at(0).at(1)-2)<d);
  
  assert(std::abs(trng.at(1).at(0)-10)<d);
  assert(std::abs(trng.at(1).at(1)-2)<d);
  
  assert(std::abs(trng.at(2).at(0)-6)<d);
  assert(std::abs(trng.at(2).at(1)-8.9282)<d);
  
  
  // Switch basis
  basis bas = switchBasis(vecd({3,3}),vecd({1,1}));
  
  assert(std::abs(bas.b1.at(0)-0.7071)<d);
  assert(std::abs(bas.b1.at(1)-0.7071)<d);
  
  assert(std::abs(bas.b2.at(0)-0.7071)<d);
  assert(std::abs(bas.b2.at(1)-(-0.7071))<d);
  
  assert(std::abs(bas.a-4.24264)<d);
  assert(std::abs(bas.b-0)<d);
  
  // Vector components
  assert(std::abs(component(vecd({3,3}),vecd({1,1}))-4.24264)<d);
  
  auto comV = componentVector(vecd({3,3}),vecd({1,1}));
  
  assert(std::abs(comV.at(0)-3)<d);
  assert(std::abs(comV.at(1)-3)<d);
  
  // Intersection point
  const auto interPoint = intersectionPoint(vecd({2,2}),vecd({14,14}),
                                            vecd({12,4}),vecd({8,16}));
  
  
  assert(std::abs(interPoint.at(0)-10)<d);
  assert(std::abs(interPoint.at(1)-10)<d);
  
  
  const auto interTime = intersectionTime(vecd({2,2}),vecd({12,12}),
                                          vecd({12,4}),vecd({-4,12}));
  
  
  // Intersection at 2/3 of vector v1
  assert(std::abs(interTime-(2.0/3))<d);
  
  
  const auto intrsc = intersection(vecd({2,2}),vecd({14,14}),
                                   vecd({12,4}),vecd({8,16}));
  
  // Intersection at 2/3 of line (a-b)
  assert(std::abs(intrsc-(2.0/3))<d);
  
  std::cout << "Exit\n";
    
}
