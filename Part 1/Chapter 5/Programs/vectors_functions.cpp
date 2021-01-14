#include "vectors_functions.h"
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

using std::vector;

// Add vectors
vector<double> addVectors(const vector<double> & v1, const vector<double> & v2){

  // Vectors must be the same size
  if(v1.size()!=v2.size()){

    // If vectors are of different sizes, return empty list
    return {};

  }else{

    vector<double> vec;

    // Add corresponding components together
    for(int i=0;i<v1.size();i++){
      vec.push_back(v1.at(i)+v2.at(i));
    }

    return vec;

  }
}

// Subtract vectors
vector<double> subVectors(const vector<double> & v1, const vector<double> & v2){
  return addVectors(v1,oppositeVector(v2));
}


vector<double> scaleVector(const vector<double> & vec, double scale){

  vector<double> nVec;

  //Scale all vector components
  for(int i=0;i<vec.size();i++){
    nVec.push_back(vec.at(i) * scale);
  }

  return nVec;

}

// Length of vector
double magnitude(const vector<double> & vec){

  double s = 0;

  // Sum squares of all components
  for(int i=0;i<vec.size();i++){
    s += pow(vec.at(i),2);
  }

  return sqrt(s);

}

// Normalize vector (create unit vector)
vector<double> norm(const vector<double> & vec){

  double m = magnitude(vec);

  if(m==0){
    // You cant normalize zero vector
    return {};
  }else{
    return scaleVector(vec,1/m);
  }

}

vector<double> normalVector(const vector<double> & vec){
  return vector<double>({ vec.at(1), -vec.at(0) });
}

// Angle between two vectors
double angleBetween(const vector<double> & v1, const vector<double> & v2){

  vector<double> v3 = subVectors(v1,v2);
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

vector<double> oppositeVector(const vector<double> & vec){

  vector<double> vctr;

  for(auto i=vec.begin();i!=vec.end();i++){
    vctr.push_back(-(*i));
  }

  return vctr;

}

double determinant(const vector<vector<double>> & array){

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
      vector<vector<double>> newmatrix;
      for(int j=1;j<size;j++){
       vector<double> row = array.at(j);
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

std::array<vector<double>,4> constructSquare(const vector<double> & a, const vector<double> & b){

  std::array<vector<double>,4> result;

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

std::array<vector<double>,3> constructEquilateralTriangle(const vector<double> & a, const vector<double> & b){

  std::array<vector<double>,3> result;

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
  vector<double> start { 450, 50 };


  // Legs

    double halfAngle = angleAtTop/2;

    // Left leg vector
    vector<double> leftLeg { -sin(halfAngle), cos(halfAngle) };
    leftLeg = scaleVector(leftLeg,legLength);

    // Right leg vector
    vector<double> rightLeg { -leftLeg.at(0), leftLeg.at(1) };

    // Absolute leg positions
    auto leftLegTarget = addVectors(start,leftLeg);
    auto rightLegTarget = addVectors(start,rightLeg);


  // Crossbar

    // Vectors to crossbar points (max width)
    vector<double> crossbarStart = scaleVector(leftLeg,crossbarHeight);
    vector<double> crossbarEnd = scaleVector(rightLeg,crossbarHeight);

    // Crossbar vector left->right (max width)
    vector<double> crossbar =
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
    vector<double> serif = scaleVector(subVectors(rightLeg,leftLeg),serifProp);

    // Serif offset
    vector<double> serifOffset = scaleVector(serif,serifAlign);

    // Left serif
    auto leftSerifBeg = subVectors(leftLegTarget,serifOffset);
    auto leftSerifEnd = addVectors(leftSerifBeg,serif);

    // Right serif
    auto rightSerifBeg = subVectors(rightLegTarget,serifOffset);
    auto rightSerifEnd = addVectors(rightSerifBeg,serif);



  // Create lines

    std::array<sf::Vertex,2> leftLegLine = {
      sf::Vertex(sf::Vector2f(start.at(0), start.at(1))),
      sf::Vertex(sf::Vector2f(leftLegTarget.at(0), leftLegTarget.at(1)))
    };

    std::array<sf::Vertex,2> rightLegLine = {
      sf::Vertex(sf::Vector2f(start.at(0), start.at(1))),
      sf::Vertex(sf::Vector2f(rightLegTarget.at(0), rightLegTarget.at(1)))
    };

    std::array<sf::Vertex,2> crossbarLine = {
      sf::Vertex(sf::Vector2f(crossbarStartTarget.at(0), crossbarStartTarget.at(1))),
      sf::Vertex(sf::Vector2f(crossbarEndTarget.at(0), crossbarEndTarget.at(1))),
    };

    std::array<sf::Vertex,2> leftSerifLine = {
      sf::Vertex(sf::Vector2f(leftSerifBeg.at(0), leftSerifBeg.at(1))),
      sf::Vertex(sf::Vector2f(leftSerifEnd.at(0), leftSerifEnd.at(1))),
    };

    std::array<sf::Vertex,2> rightSerifLine = {
      sf::Vertex(sf::Vector2f(rightSerifBeg.at(0), rightSerifBeg.at(1))),
      sf::Vertex(sf::Vector2f(rightSerifEnd.at(0), rightSerifEnd.at(1))),
    };



  // Render lines
  
    std::vector<std::array<sf::Vertex,2>> lines;
    
    lines.push_back(leftLegLine); lines.push_back(rightLegLine);
    lines.push_back(crossbarLine); lines.push_back(leftSerifLine);
    lines.push_back(rightSerifLine);
    
    renderLines(lines);

}

void renderLines(const std::vector<std::array<sf::Vertex,2>> & lines){
  
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
      sf::Vertex ln [] = {(*pt).at(0),(*pt).at(1)};
      wnd.draw(ln,2,sf::Lines);
    }

    wnd.display();

  }
}


std::vector<double> curvedPath(const std::vector<double> & endPoint,
                              const std::vector<double> & currentPoint, double speed,
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

void drawCurvedPath(const std::vector<double> & endPoint,
                    const std::vector<double> & currentPoint, double speed,
                    double normalProportion, double timeStep){
  
  
  std::vector<std::array<sf::Vertex,2>> lines;
  
  auto cp = currentPoint; auto lastPoint = cp;
  
  // Loop while cp != target
  while (cp.at(0)!=endPoint.at(0)||cp.at(1)!=endPoint.at(1)) {
    
    cp = curvedPath(endPoint,cp,speed,normalProportion,timeStep);
    
    auto arr = std::array<sf::Vertex,2>({sf::Vertex(sf::Vector2f(lastPoint.at(0), lastPoint.at(1))),sf::Vertex(sf::Vector2f(cp.at(0), cp.at(1)))});
    
    lastPoint = cp;
    
    lines.push_back(arr);
    
  }
  
  renderLines(lines);
  
}

std::pair<std::vector<double>,double>
  madPath(const std::vector<double> & endPoint,
          const std::vector<double> & currentPoint,
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

void drawMadPath(const std::vector<double> & endPoint,
                 const std::vector<double> & currentPoint,
                 double currentAlpha,
                 double speed,
                 double alphaSpeed,
                 double timeStep){
    
  std::cout << "Draw Mad Path\n";
  
  std::vector<std::array<sf::Vertex,2>> lines;
  
  auto cp = currentPoint; auto lastPoint = cp;
  
  // Loop while cp != target
  while (cp.at(0)!=endPoint.at(0)||cp.at(1)!=endPoint.at(1)) {
    
    auto pointAlpha =
      madPath(endPoint,cp,currentAlpha,speed,alphaSpeed,timeStep);
    
    cp = pointAlpha.first; currentAlpha = pointAlpha.second;
    
    auto arr = std::array<sf::Vertex,2>({sf::Vertex(sf::Vector2f(lastPoint.at(0), lastPoint.at(1))),sf::Vertex(sf::Vector2f(cp.at(0), cp.at(1)))});
    
    lastPoint = cp; lines.push_back(arr);
    
  }
  
  renderLines(lines);
            
}

basis switchBasis(const std::vector<double> & vec,
                 const std::vector<double> & directionVec){

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

double component(const std::vector<double> & vec,
                const std::vector<double> & directionVec){
  
  auto alpha = atan2(directionVec.at(1),directionVec.at(0));
  auto theta = atan2(vec.at(1),vec.at(0));
  
  auto mag = magnitude(vec);
  
  return mag*cos(theta-alpha);
  
}

std::vector<double> componentVector(const std::vector<double> & vec,
                                   const std::vector<double> & directionVec){
  
  auto v = norm(directionVec);
  
  return scaleVector(v,component(vec,directionVec));
  
}

std::vector<double> intersectionPoint(const std::vector<double> & a,
                                      const std::vector<double> & b,
                                      const std::vector<double> & c,
                                      const std::vector<double> & d){
  
  auto tc1 = b.at(0)-a.at(0);
  auto tc2 = b.at(1)-a.at(1);
  
  auto sc1 = c.at(0)-d.at(0);
  auto sc2 = c.at(1)-d.at(1);
  
  auto con1 = c.at(0)-a.at(0);
  auto con2 = c.at(1)-a.at(1);
  
  auto det = (tc2*sc1-tc1*sc2);
  
  if(det==0){
    // No unique solution
    return std::vector<double>({});
  } else {
    auto con = tc2*con1-tc1*con2;
    auto s = con/det;
    
    auto dc = subVectors(d,c);
    auto sdc = scaleVector(dc,s);
    return addVectors(c,sdc);
  }
  
}


// Point1, Vector1, Point2, Vector2
double intersectionTime(std::vector<double> p1,
                        std::vector<double> v1,
                        std::vector<double> p2,
                        std::vector<double> v2){

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

double intersection(const std::vector<double> & a,
                    const std::vector<double> & b,
                    const std::vector<double> & c,
                    const std::vector<double> & d){

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

