#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "../Programs/geometry3d_functions.h"

// g++ -c ex1.cpp ../Programs/geometry3d_functions.cpp && g++ ex1.o geometry3d_functions.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system && ./a.out

using std::cout;
using std::endl;
using std::array;
using sf::Vertex;
using sf::Vector2f;
typedef array<vector3d,8> cube;

int main(){

  sf::RenderWindow wnd(sf::VideoMode(1024, 768), "Graphics 3D", sf::Style::Close);
  wnd.setFramerateLimit(30);

  const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;


  cube cb { { {0,100,100}, {100,100,100},
              {0,0,100}, {100,0,100},

              {0,100,0}, {100,100,0},
              {0,0,0}, {100,0,0} } };

  vector3d observerPosition = { -50, 70, -500 }; // Horizontal, vertical, depth
  const vector3d observerVector = { 0, 0, 1 };
  vector3d observerUp = { 0, 1, 0 };
  float halfViewAngle = 0.6;
  float height = 600;


  int maxDistanceIndex = 0;
  float bestDistance = magnitude3d(sub3d(cb[0],observerPosition));

  for(int i=1;i<8;i++){
    float bd = magnitude3d(sub3d(cb[i],observerPosition));
    if(bd > bestDistance) {
      maxDistanceIndex = i;
      bestDistance = bd;
    }
  }

  array<vector2d,8> cube2d;

  for(int i=0;i<8;i++) {
    cube2d[i] = pos3DToScreenPos(cb[i],
                                 observerPosition,
                                 observerVector,
                                 observerUp,
                                 halfViewAngle,
                                 height);

    cube2d[i][0] += 400;
    cube2d[i][1] += 160;
  }


  //return 0;

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

    //observerPosition = add3d(observerPosition,{0,0,1});

//     for(int i=0;i<8;i++) {
//       cube2d[i] = pos3DToScreenPos(cb[i],
//                                   observerPosition,
//                                   observerVector,
//                                   observerUp,
//                                   halfViewAngle,
//                                   height);
//
//       cube2d[i][0] += 400;
//       cube2d[i][1] += 160;
//     }

    wnd.clear();

    Vertex a[] = { Vertex(Vector2f(cube2d[0][0], cube2d[0][1])),
                   Vertex(Vector2f(cube2d[1][0], cube2d[1][1])) };
    Vertex b[] = { Vertex(Vector2f(cube2d[0][0], cube2d[0][1])),
                   Vertex(Vector2f(cube2d[2][0], cube2d[2][1])) };
    Vertex c[] = { Vertex(Vector2f(cube2d[1][0], cube2d[1][1])),
                   Vertex(Vector2f(cube2d[3][0], cube2d[3][1])) };
    Vertex d[] = { Vertex(Vector2f(cube2d[2][0], cube2d[2][1])),
                   Vertex(Vector2f(cube2d[3][0], cube2d[3][1])) };

    Vertex e[] = { Vertex(Vector2f(cube2d[0][0], cube2d[0][1])),
                   Vertex(Vector2f(cube2d[4][0], cube2d[4][1])) };
    Vertex f[] = { Vertex(Vector2f(cube2d[1][0], cube2d[1][1])),
                   Vertex(Vector2f(cube2d[5][0], cube2d[5][1])) };
    Vertex g[] = { Vertex(Vector2f(cube2d[2][0], cube2d[2][1])),
                   Vertex(Vector2f(cube2d[6][0], cube2d[6][1])) };
    Vertex h[] = { Vertex(Vector2f(cube2d[3][0], cube2d[3][1])),
                   Vertex(Vector2f(cube2d[7][0], cube2d[7][1])) };

    Vertex i[] = { Vertex(Vector2f(cube2d[4][0], cube2d[4][1])),
                   Vertex(Vector2f(cube2d[5][0], cube2d[5][1])) };
    Vertex j[] = { Vertex(Vector2f(cube2d[4][0], cube2d[4][1])),
                   Vertex(Vector2f(cube2d[6][0], cube2d[6][1])) };
    Vertex k[] = { Vertex(Vector2f(cube2d[5][0], cube2d[5][1])),
                   Vertex(Vector2f(cube2d[7][0], cube2d[7][1])) };
    Vertex l[] = { Vertex(Vector2f(cube2d[6][0], cube2d[6][1])),
                   Vertex(Vector2f(cube2d[7][0], cube2d[7][1])) };


    // Center
    Vertex cent[] = { Vertex(Vector2f(400, 160)),
                      Vertex(Vector2f(410, 160)) };

    wnd.draw(a, 2, sf::Lines);
    wnd.draw(b, 2, sf::Lines);
    wnd.draw(c, 2, sf::Lines);
    wnd.draw(d, 2, sf::Lines);

    wnd.draw(e, 2, sf::Lines);
    wnd.draw(f, 2, sf::Lines);
    wnd.draw(g, 2, sf::Lines);
    wnd.draw(h, 2, sf::Lines);

    wnd.draw(i, 2, sf::Lines);
    wnd.draw(j, 2, sf::Lines);
    wnd.draw(k, 2, sf::Lines);
    wnd.draw(l, 2, sf::Lines);

    wnd.draw(cent, 2, sf::Lines);

    wnd.display();

  }

  std::cout << "Part 4 - Chapter 17 - Exercise 1\n";
}
