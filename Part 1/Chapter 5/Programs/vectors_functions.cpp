#include "vectors_functions.h"
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

using std::vector;
using std::array;
using sf::Vertex;
using sf::Vector2f;

typedef vector<double> vecd;


// Add vectors
vecd addVectors(const vecd & v1, const vecd & v2){

  // Vectors must be the same size
  if(v1.size()!=v2.size()){

    // If vectors are of different sizes, return empty list
    return {};

  }else{

    vecd vec;

    // Add corresponding components together
    for(int i=0;i<v1.size();i++){
      vec.push_back(v1.at(i)+v2.at(i));
    }

    return vec;

  }
}

// Subtract vectors
vecd subVectors(const vecd & v1, const vecd & v2){
  return addVectors(v1,oppositeVector(v2));
}


vecd scaleVector(const vecd & vec, double scale){

  vecd nVec;

  //Scale all vector components
  for(int i=0;i<vec.size();i++){
    nVec.push_back(vec.at(i) * scale);
  }

  return nVec;

}

// Length of vector
double magnitude(const vecd & vec){

  double s = 0;

  // Sum squares of all components
  for(int i=0;i<vec.size();i++){
    s += pow(vec.at(i),2);
  }

  return sqrt(s);

}

// Normalize vector (create unit vector)
vecd norm(const vecd & vec){

  double m = magnitude(vec);

  if(m==0){
    // You cant normalize zero vector
    return {};
  }else{
    return scaleVector(vec,1/m);
  }

}

vecd normalVector(const vecd & vec){
  return vecd({ vec.at(1), -vec.at(0) });
}

// Angle between two vectors
double angleBetween(const vecd & v1, const vecd & v2){

  vecd v3 = subVectors(v1,v2);
  double m1 = magnitude(v1);
  double m2 = magnitude(v2);
  double m3 = magnitude(v3);

  // Zero vector or vectors are equal
  if((0==m1||0==m2)||0==m3){

    return 0;

  }else{

    // Calculate angle from cosine rule
    return acos((pow(m1,2) + pow(m2,2) - pow(m3,2))/(2*m1*m2));

  }

}

vecd oppositeVector(const vecd & vec){

  vecd vctr;

  for(auto i=vec.begin();i!=vec.end();i++){
    vctr.push_back(-(*i));
  }

  return vctr;

}

double determinant(const vector<vecd> & array){

  int size = array.size();

  if(1==size){

    return array.at(0).at(0);

  }else{

    int mult = 1; double sum = 0;

    // Loop through first row
    for(int i=0;i<size;i++){

      // Value from top row
      double el = array.at(0).at(i);

      // New matrix consists of remaining rows
      // without values at current index (i).
      vector<vecd> newmatrix;
      for(int j=1;j<size;j++){
       vecd row = array.at(j);
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

array<vecd,4> constructSquare(const vecd & a, const vecd & b){

  array<vecd,4> result;

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

array<vecd,3> constructEquilateralTriangle(const vecd & a, const vecd & b){

  array<vecd,3> result;

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
void createA(double legLength, double angleAtTop, double serifProp,
             double crossbarProp, double crossbarHeight, double serifAlign,
             double crossbarAlign){

  // Starting position
  vecd start { 450, 50 };


  // Legs

    double halfAngle = angleAtTop/2;

    // Left leg vector
    vecd leftLeg { -sin(halfAngle), cos(halfAngle) };
    leftLeg = scaleVector(leftLeg,legLength);

    // Right leg vector
    vecd rightLeg { -leftLeg.at(0), leftLeg.at(1) };

    // Absolute leg positions
    auto leftLegTarget = addVectors(start,leftLeg);
    auto rightLegTarget = addVectors(start,rightLeg);


  // Crossbar

    // Vectors to crossbar points (max width)
    vecd crossbarStart = scaleVector(leftLeg,crossbarHeight);
    vecd crossbarEnd = scaleVector(rightLeg,crossbarHeight);

    // Crossbar vector left->right (max width)
    vecd crossbar =
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
    vecd serif = scaleVector(subVectors(rightLeg,leftLeg),serifProp);

    // Serif offset
    vecd serifOffset = scaleVector(serif,serifAlign);

    // Left serif
    auto leftSerifBeg = subVectors(leftLegTarget,serifOffset);
    auto leftSerifEnd = addVectors(leftSerifBeg,serif);

    // Right serif
    auto rightSerifBeg = subVectors(rightLegTarget,serifOffset);
    auto rightSerifEnd = addVectors(rightSerifBeg,serif);



  // Create lines

    array<Vertex,2> leftLegLine = {
      Vertex(Vector2f(start.at(0), start.at(1))),
      Vertex(Vector2f(leftLegTarget.at(0), leftLegTarget.at(1)))
    };

    array<Vertex,2> rightLegLine = {
      Vertex(Vector2f(start.at(0), start.at(1))),
      Vertex(Vector2f(rightLegTarget.at(0), rightLegTarget.at(1)))
    };

    array<Vertex,2> crossbarLine = {
      Vertex(Vector2f(crossbarStartTarget.at(0), crossbarStartTarget.at(1))),
      Vertex(Vector2f(crossbarEndTarget.at(0), crossbarEndTarget.at(1))),
    };

    array<Vertex,2> leftSerifLine = {
      Vertex(Vector2f(leftSerifBeg.at(0), leftSerifBeg.at(1))),
      Vertex(Vector2f(leftSerifEnd.at(0), leftSerifEnd.at(1))),
    };

    array<Vertex,2> rightSerifLine = {
      Vertex(Vector2f(rightSerifBeg.at(0), rightSerifBeg.at(1))),
      Vertex(Vector2f(rightSerifEnd.at(0), rightSerifEnd.at(1))),
    };



  // Render lines
  
    vector<array<Vertex,2>> lines;
    
    lines.push_back(leftLegLine); lines.push_back(rightLegLine);
    lines.push_back(crossbarLine); lines.push_back(leftSerifLine);
    lines.push_back(rightSerifLine);
    
    renderLines(lines);

}

void renderLines(const vector<array<Vertex,2>> & lines){
  
  sf::RenderWindow wnd(sf::VideoMode(1024, 768), "Vectors", sf::Style::Close);
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
    
    for(auto pt = lines.begin(); pt!=lines.end(); pt++){
      Vertex ln [] = {(*pt).at(0),(*pt).at(1)};
      wnd.draw(ln,2,sf::Lines);
    }

    wnd.display();

  }
}


vecd curvedPath(const vecd & endPoint,
                              const vecd & currentPoint, double speed,
                              double normalProportion, double timeStep){
  
  auto radius = subVectors(endPoint,currentPoint);
  
  auto mag = magnitude(radius);
  
  if(mag<speed*timeStep){
    return endPoint;
  } else {
    
    auto radialComponent = norm(radius);
    auto tangentialComponent =
      scaleVector(normalVector(radialComponent),normalProportion);
      
    auto velocity =
      scaleVector((addVectors(radialComponent,
                              tangentialComponent)),
                   speed);
      
    auto currentPosition = addVectors(currentPoint,velocity);
    
    return currentPosition;
    
  }
  
}

void drawCurvedPath(const vecd & endPoint,
                    const vecd & currentPoint, double speed,
                    double normalProportion, double timeStep){
  
  
  vector<array<Vertex,2>> lines;
  
  auto cp = currentPoint; auto lastPoint = cp;
  
  // Loop while cp != target
  while (cp.at(0)!=endPoint.at(0)||cp.at(1)!=endPoint.at(1)) {
    
    cp = curvedPath(endPoint,cp,speed,normalProportion,timeStep);
    
    auto arr = array<Vertex,2>({Vertex(Vector2f(lastPoint.at(0), lastPoint.at(1))),Vertex(Vector2f(cp.at(0), cp.at(1)))});
    
    lastPoint = cp;
    
    lines.push_back(arr);
    
  }
  
  renderLines(lines);
  
}

std::pair<vecd,double>
  madPath(const vecd & endPoint,
          const vecd & currentPoint,
          double currentAlpha,
          double speed,
          double alphaSpeed,
          double timeStep){

  auto radius = subVectors(endPoint,currentPoint);
  auto mag = magnitude(radius);
  
  if(mag<speed*timeStep){
    return std::make_pair(endPoint,currentAlpha);
  } else {
    
    auto radialComponent = norm(radius);
    auto newAlpha = currentAlpha + alphaSpeed*timeStep;
    
    auto tanNewAlpha = tan(newAlpha);
    
    auto tangentialComponent =
      scaleVector(normalVector(radialComponent),
                  tanNewAlpha);
    
    auto vec = addVectors(radialComponent,tangentialComponent);
    auto velocity = scaleVector(norm(vec),speed);
    
    return std::make_pair(addVectors(currentPoint,velocity),
                          newAlpha);
    
  }
  
}

void drawMadPath(const vecd & endPoint,
                 const vecd & currentPoint,
                 double currentAlpha,
                 double speed,
                 double alphaSpeed,
                 double timeStep){
    
  vector<array<Vertex,2>> lines;
  
  auto cp = currentPoint; auto lastPoint = cp;
  
  // Loop while cp != target
  while (cp.at(0)!=endPoint.at(0)||cp.at(1)!=endPoint.at(1)) {
    
    auto pointAlpha =
      madPath(endPoint,cp,currentAlpha,speed,alphaSpeed,timeStep);
    
    cp = pointAlpha.first; currentAlpha = pointAlpha.second;
    
    auto arr = array<Vertex,2>({Vertex(Vector2f(lastPoint.at(0), lastPoint.at(1))),Vertex(Vector2f(cp.at(0), cp.at(1)))});
    
    lastPoint = cp; lines.push_back(arr);
    
  }
  
  renderLines(lines);
            
}

basis switchBasis(const vecd & vec,
                 const vecd & directionVec){

  // Unit vector
  auto basis1 = norm(directionVec);
  
  // Perpendicular to basis1
  auto basis2 = normalVector(basis1);
  
  // Alpha angle(between basis1 and x axis)
  auto alpha = atan2(basis1.at(1),basis1.at(0));
  
  // Theta angle(between original vec and x axis)
  auto theta = atan2(vec.at(1),vec.at(0));
  
  // Magnitude of original vector
  auto mag = magnitude(vec);
  
  // -(alpha - theta)
  auto df = theta - alpha;
  
  // cos(df) = a/mag(v)
  auto a = mag*cos(df);
  
  // sin(df) = b/mag(v)
  auto b = mag*sin(df);
  
  return basis({ basis1, basis2, a, b });
  
}

double component(const vecd & vec,
                const vecd & directionVec){
  
  auto alpha = atan2(directionVec.at(1),directionVec.at(0));
  auto theta = atan2(vec.at(1),vec.at(0));
  
  auto mag = magnitude(vec);
  
  return mag*cos(theta-alpha);
  
}

vecd componentVector(const vecd & vec,
                                   const vecd & directionVec){
  
  auto v = norm(directionVec);
  
  return scaleVector(v,component(vec,directionVec));
  
}

vecd intersectionPoint(const vecd & a,
                                      const vecd & b,
                                      const vecd & c,
                                      const vecd & d){
  
  auto tc1 = b.at(0)-a.at(0);
  auto tc2 = b.at(1)-a.at(1);
  
  auto sc1 = c.at(0)-d.at(0);
  auto sc2 = c.at(1)-d.at(1);
  
  auto con1 = c.at(0)-a.at(0);
  auto con2 = c.at(1)-a.at(1);
  
  auto det = (tc2*sc1-tc1*sc2);
  
  if(det==0){
    // No unique solution
    return vecd({});
  } else {
    auto con = tc2*con1-tc1*con2;
    auto s = con/det;
    
    auto dc = subVectors(d,c);
    auto sdc = scaleVector(dc,s);
    return addVectors(c,sdc);
  }
  
}


// Point1, Vector1, Point2, Vector2
double intersectionTime(vecd p1,
                        vecd v1,
                        vecd p2,
                        vecd v2){

  auto tc1 = v1.at(0);
  auto tc2 = v1.at(1);
  
  auto sc1 = v2.at(0);
  auto sc2 = v2.at(1);
  
  auto con1 = p2.at(0)-p1.at(0);
  auto con2 = p2.at(1)-p1.at(1);
  
  auto det = tc2*sc1-tc1*sc2;
  
  if(det==0){
    // No unique solution
    return 0;
  } else {
    auto con = sc1*con2-sc2*con1;
    auto t = con/det;
    return t;
  }
  
}

double intersection(const vecd & a,
                    const vecd & b,
                    const vecd & c,
                    const vecd & d){

  auto tc1 = b.at(0)-a.at(0);
  auto tc2 = b.at(1)-a.at(1);
  
  auto sc1 = c.at(0)-d.at(0);
  auto sc2 = c.at(1)-d.at(1);
  
  auto con1 = c.at(0)-a.at(0);
  auto con2 = c.at(1)-a.at(1);
  
  auto det = (tc2*sc1-tc1*sc2);
  
  if(det==0){
    // No unique solution
    return 0;
  } else {
    
    auto con = tc2*con1-tc1*con2;
    auto s = con/det;
    
    if(s<0||s>1){
      return 0; // false
    } else {
      
      double t =
        tc1 != 0 ? (con1-s*sc1)/tc1 :
                   (con2-s*sc2)/tc2;
                   
      if(t<0||t>1){
        return 0; // none
      } else {
        return t;
      }
      
    }
    
  }
  
}

void drawArrowhead(double lineSegment,double size, double angle){
  
  vecd start { 200, 200 };

  double halfAngle = angle/2;
  
  vecd leftPart { cos(halfAngle), sin(halfAngle) };
  leftPart = scaleVector(leftPart,size);
  
  vecd rightPart { cos(halfAngle), -sin(halfAngle) };
  rightPart = scaleVector(rightPart,size);
  
  auto leftPartTarget = addVectors(start,leftPart);
  auto rightPartTarget = addVectors(start,rightPart);
  
  auto halfBack =
    scaleVector(subVectors(leftPartTarget,
                           rightPartTarget),
                0.5);
  
  auto tail =
    scaleVector(norm(normalVector(halfBack)),
                lineSegment);

  auto midBack = addVectors(rightPartTarget,halfBack);
  
  auto finalTarget = addVectors(midBack,tail);
  
  
  vector<array<Vertex,2>> lines;
  
  array<Vertex,2> leftPartLine = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(leftPartTarget.at(0), leftPartTarget.at(1)))
  };
  
  array<Vertex,2> rightPartLine = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(rightPartTarget.at(0), rightPartTarget.at(1)))
  };
  
  array<Vertex,2> backLine = {
    Vertex(Vector2f(leftPartTarget.at(0), leftPartTarget.at(1))),
    Vertex(Vector2f(rightPartTarget.at(0), rightPartTarget.at(1)))
  };
  
  array<Vertex,2> tailLine = {
    Vertex(Vector2f(midBack.at(0), midBack.at(1))),
    Vertex(Vector2f(finalTarget.at(0), finalTarget.at(1)))
  };
  
  lines.push_back(leftPartLine);
  lines.push_back(rightPartLine);
  lines.push_back(backLine);
  lines.push_back(tailLine);
  
  
  renderLines(lines);
  
}

void drawKite(double lineSegment, double height, double width, double angle){
  
  
  // Main part
  
    const vecd start { 200, 300 }; const vecd main { height, 0 };
    
    const auto rightEnd = addVectors(start,main);
      
    const auto toMid = scaleVector(main,1.0/3);
    
    const auto midPoint = addVectors(start,toMid);

    const auto vert = scaleVector(norm(normalVector(toMid)),width);
    
    const auto vertStart = addVectors(midPoint,scaleVector(vert,0.5));
    
    const auto vertTarget = addVectors(vertStart,oppositeVector(vert));
    
  // Tail
        
    const auto tailDown =
      scaleVector({ cos(angle), sin(angle) },
                  lineSegment);
    
    const auto tailUp =
      scaleVector({ cos(angle), -sin(angle) },
                  lineSegment);
    
    const auto tailTarget1 = addVectors(rightEnd,tailDown);
    const auto tailTarget2 = addVectors(tailTarget1,tailUp);
    const auto tailTarget3 = addVectors(tailTarget2,tailDown);
    
  
  vector<array<Vertex,2>> lines;
  
  array<Vertex,2> mainLine = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(rightEnd.at(0), rightEnd.at(1)))
  };
  
  array<Vertex,2> verticalLine = {
    Vertex(Vector2f(vertStart.at(0), vertStart.at(1))),
    Vertex(Vector2f(vertTarget.at(0), vertTarget.at(1)))
  };
  
  array<Vertex,2> topRight = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(vertStart.at(0), vertStart.at(1)))
  };
  
  array<Vertex,2> topLeft = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(vertTarget.at(0), vertTarget.at(1)))
  };
  
  array<Vertex,2> botRight = {
    Vertex(Vector2f(vertStart.at(0), vertStart.at(1))),
    Vertex(Vector2f(rightEnd.at(0), rightEnd.at(1)))
  };
  
  array<Vertex,2> botLeft = {
    Vertex(Vector2f(vertTarget.at(0), vertTarget.at(1))),
    Vertex(Vector2f(rightEnd.at(0), rightEnd.at(1)))
  };
  
  
  array<Vertex,2> tailA = {
    Vertex(Vector2f(rightEnd.at(0), rightEnd.at(1))),
    Vertex(Vector2f(tailTarget1.at(0), tailTarget1.at(1)))
  };
  
  array<Vertex,2> tailB = {
    Vertex(Vector2f(tailTarget1.at(0), tailTarget1.at(1))),
    Vertex(Vector2f(tailTarget2.at(0), tailTarget2.at(1)))
  };
  
  array<Vertex,2> tailC = {
    Vertex(Vector2f(tailTarget2.at(0), tailTarget2.at(1))),
    Vertex(Vector2f(tailTarget3.at(0), tailTarget3.at(1)))
  };
  
  
  lines.push_back(mainLine);
  lines.push_back(verticalLine);
  
  lines.push_back(topRight);
  lines.push_back(topLeft);
  
  lines.push_back(botRight);
  lines.push_back(botLeft);
  
  lines.push_back(tailA);
  lines.push_back(tailB);
  lines.push_back(tailC);
  
  renderLines(lines);
  
}

void drawCube(double side, double angle, double depth){
  
  // A1
  const vecd start { 200, 300 };
  
  // Horizontal vector
  const vecd hori { side, 0 };
  
  // Vertical vector
  const vecd veri = normalVector(hori);
  
  // Diagonal vector
  vecd diagv ({ cos(angle), -sin(angle) });
  diagv = scaleVector(diagv,depth);
  
  const auto b1 = addVectors(start,hori);
  
  const auto c1 = addVectors(b1,veri);
  
  const auto d1 = addVectors(start,veri);
  
  const auto a2 = addVectors(start,diagv);
  
  const auto b2 = addVectors(b1,diagv);
  
  const auto c2 = addVectors(c1,diagv);
  
  const auto d2 = addVectors(d1,diagv);
  
  vector<array<Vertex,2>> lines;
  
  array<Vertex,2> ab = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(b1.at(0), b1.at(1)))
  };
  
  array<Vertex,2> bc = {
    Vertex(Vector2f(b1.at(0), b1.at(1))),
    Vertex(Vector2f(c1.at(0), c1.at(1)))
  };
  
  array<Vertex,2> cd = {
    Vertex(Vector2f(c1.at(0), c1.at(1))),
    Vertex(Vector2f(d1.at(0), d1.at(1)))
  };
  
  array<Vertex,2> ad = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(d1.at(0), d1.at(1)))
  };
  
  array<Vertex,2> aa2 = {
    Vertex(Vector2f(start.at(0), start.at(1))),
    Vertex(Vector2f(a2.at(0), a2.at(1)))
  };
  
  array<Vertex,2> bb2 = {
    Vertex(Vector2f(b1.at(0), b1.at(1))),
    Vertex(Vector2f(b2.at(0), b2.at(1)))
  };
  
  array<Vertex,2> cc2 = {
    Vertex(Vector2f(c1.at(0), c1.at(1))),
    Vertex(Vector2f(c2.at(0), c2.at(1)))
  };
  
  array<Vertex,2> dd2 = {
    Vertex(Vector2f(d1.at(0), d1.at(1))),
    Vertex(Vector2f(d2.at(0), d2.at(1)))
  };
  
  array<Vertex,2> a2b2 = {
    Vertex(Vector2f(a2.at(0), a2.at(1))),
    Vertex(Vector2f(b2.at(0), b2.at(1)))
  };
  
  array<Vertex,2> b2c2 = {
    Vertex(Vector2f(b2.at(0), b2.at(1))),
    Vertex(Vector2f(c2.at(0), c2.at(1)))
  };
  
  array<Vertex,2> c2d2 = {
    Vertex(Vector2f(c2.at(0), c2.at(1))),
    Vertex(Vector2f(d2.at(0), d2.at(1)))
  };
  
  array<Vertex,2> d2a2 = {
    Vertex(Vector2f(d2.at(0), d2.at(1))),
    Vertex(Vector2f(a2.at(0), a2.at(1)))
  };
  
  
  // Front
  lines.push_back(ab);
  lines.push_back(bc);
  lines.push_back(cd);
  lines.push_back(ad);
  
  // Diagonal
  lines.push_back(aa2);
  lines.push_back(bb2);
  lines.push_back(cc2);
  lines.push_back(dd2);
  
  // Back
  lines.push_back(a2b2);
  lines.push_back(b2c2);
  lines.push_back(c2d2);
  lines.push_back(d2a2);
  
  
  renderLines(lines);
  
}

void drawShape(int index){
  
  switch(index){
    
    case 1:
      
      createA(200, // leg length
              1.7, // angle at top (radians)
              0.45, // serif proportion (0-1)
              0.5, // crossbar proportion (0-1)
              0.4, // crossbar position, larger=lower (0-1)
              0.5, // serif align (0-1)
              0.5); // crossbar align, left/right/center (0-1)
          
      break;
      
    case 2:
      
      drawCurvedPath(vecd({200,250}), // end point
                     vecd({200,20}), // current point
                     1, // speed
                     2.2, // normal proportion(larger = more curved)
                     5.5); // time step(larger = earlier and bigger last step)
      break;
      
    case 3:
      
      drawMadPath(vecd({400,250}),
                  vecd({200,20}),
                  2, // current alpha
                  4.5, // speed
                  6.32, // alpha speed
                  4.5); // time step
      
      break;
      
    case 4:
      
      drawArrowhead(200, // line segment
                    150, // size
                    0.5); // angle
      
      break;
      
    case 5:
      
      drawKite(110, // line segment
               225, // height
               135, // width
               0.22); // angle
      
      break;
      
    case 6:
      
      drawCube(100, // side
               0.35, // angle
               60); // depth
      
      break;
      
    default:
      
      std::cout << "Wrong index\n";
      
      break;
      
  }
  
}



