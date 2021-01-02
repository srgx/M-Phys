#include "vectors_functions.h"
#include <cassert>
#include <cmath>
#include <iostream>

typedef std::vector<float> vecf;

// g++ -c vectors.cpp vectors_functions.cpp
// g++ vectors.o vectors_functions.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

int main(){

  const float mg = sqrt(109);
  const float d = 1e-5;

  // Add Vectors
  assert(addVectors(vecf({ 3, 4 }),
                    vecf({ 7, 16 })) ==
                    vecf({ 10, 20 }));
  assert(addVectors(vecf({ 3, 4 }),
                    vecf({ 0, 0 })) ==
                    vecf({ 3, 4 }));
  assert(addVectors(vecf({ 3, 4, }),
                    vecf({ 7, 16, 22 })) ==
                    vecf());

  // Sub Vectors
  assert(subVectors(vecf({ 3, 4 }),
                    vecf({ 7, 16 })) ==
                    vecf({ -4, -12 }));
  assert(subVectors(vecf({ 3, 4 }),
                    vecf({ 2, 1 })) ==
                    vecf({ 1, 3 }));
  assert(subVectors(vecf({ 3, 4, }),
                    vecf({ 7, 16, 22 })) ==
                    vecf());

  // Scale Vectors
  assert(scaleVector(vecf({ 15, 30 }), 3) ==
                     vecf({ 45, 90 }));
  assert(scaleVector(vecf({ 20 , 10 }), 1.5) ==
                     vecf({ 30, 15 }));
  assert(scaleVector(vecf({ 12 , 22 }), 0) ==
                     vecf({ 0, 0 }));

  // Vector Magnitude
  assert(magnitude(vecf({ 3, 4 })) == 5);
  assert(magnitude(vecf({ 5, 12 })) == 13);
  assert(std::abs(magnitude(vecf({ 3, 6, 8 }))-mg)<d);

  // Normalize Vector
  assert(norm(vecf({ 0, 0 })) == vecf({}));
  vecf vec = norm(vecf({ 3, 4 }));
  assert(std::abs(vec.at(0)-3.0/5)<d);
  assert(std::abs(vec.at(1)-4.0/5)<d);
  vec = norm(vecf({ 5, 12 }));
  assert(std::abs(vec.at(0)-5.0/13)<d);
  assert(std::abs(vec.at(1)-12.0/13)<d);
  vec = norm(vecf({ 3, 6, 8 }));
  assert(std::abs(vec.at(0)-3/mg)<d);
  assert(std::abs(vec.at(1)-6/mg)<d);
  assert(std::abs(vec.at(2)-8/mg)<d);

  // Opposite Vector
  assert(oppositeVector(vecf({ 3, 4 })) ==
                        vecf({ -3, -4}));
  assert(oppositeVector(vecf({ 0, -5 })) ==
                        vecf({ 0, 5}));
  assert(oppositeVector(vecf({ 0, 0 })) ==
                        vecf({ 0, 0}));


  // Vectors Angle
  assert(angleBetween(vecf({ 5, 6 }),
                      vecf({ 5, 6 })) == 0);
  assert(angleBetween(vecf({ 5, 6 }),
                      vecf({ 0, 0 })) == 0);
  assert(std::abs(angleBetween(vecf({ 3, 4 }),
                               vecf({ 4, 3 })) - 0.2838)<d);
  assert(std::abs(angleBetween(vecf({ 5, 0 }),
                               vecf({ 0, 5 })) - M_PI/2)<d);
  assert(std::abs(angleBetween(vecf({ 5, 0 }),
                               vecf({ 5, 5 })) - M_PI/4)<d);


  // Determinant
  std::vector<vecf> mx {
    { 1, 3, 2 },
    { -3, -1, -3 },
    { 2, 3, 1 },
  };
  assert(determinant(mx)==-15);

  mx = std::vector<vecf>({{ 2, -3, 1 },
                          { 2, 0, -1 },
                          { 1, 4, 5 }});
  assert(determinant(mx)==49);

  // Normal vector(perpendicular)
  assert(normalVector(vecf({ 2, 3 })) == vecf({ 3, -2 }));
  assert(normalVector(vecf({ 5, 7 })) == vecf({ 7, -5 }));
  assert(normalVector(vecf({ 4, 0 })) == vecf({ 0, -4 }));
  assert(normalVector(vecf({ 0, 9 })) == vecf({ 9, 0 }));


  // Construct square
  vecf a { 2, 3 }; vecf b { 2, 0 };
  assert(constructSquare(a,b)==(std::array<std::vector<float>,4>({{
    { 2, 3 }, { 2, 0 },
    { 5, 3 }, { 5, 0 }}
  })));

  a = vecf({ 5, 2 }); b = vecf({ 2, 1 });
  assert(constructSquare(a,b)==(std::array<std::vector<float>,4>({{
    { 5, 2 }, { 2, 1 },
    { 6, -1 }, { 3, -2 }}
  })));

  
  // Construct equilateral triangle
  auto trng = constructEquilateralTriangle(vecf({ 2, 2 }), vecf({ 10, 2 }));


  // Render shapes
  
  drawCurvedPath(std::vector<float>({500,500}), // end point
                 std::vector<float>({300,300}), // current point
                 5, // speed
                 2, // normal proportion
                 1); // time step
  
  return 0;

  createA(200, // leg length
          1.7, // angle at top (radians)
          0.45, // serif proportion (0-1)
          0.5, // crossbar proportion (0-1)
          0.4, // crossbar position, larger=lower (0-1)
          0.5, // serif align (0-1)
          0.5); // crossbar align, left/right/center (0-1)

}
