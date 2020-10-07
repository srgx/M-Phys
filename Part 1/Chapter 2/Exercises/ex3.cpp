#include <iostream>
#include <cassert>
#include "../Programs/functions.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

// g++ -c ex3.cpp ../Programs/functions.cpp
// g++ ex3.o functions.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

void processInput(sf::RenderWindow & wnd);

int main(){

  // Multiply with logarithms
  assert(multiplyLog(1,8)==8);
  assert(multiplyLog(5,8)==40);
  assert(multiplyLog(9,6)==54);
  assert(multiplyLog(4,2.5)==10);
  assert(multiplyLog(2.25,2.25)==5.0625);


  // Graphical Slider

  sf::RenderWindow wnd(sf::VideoMode(1024, 768), "Slider", sf::Style::Close);
  wnd.setFramerateLimit(30);

  const float SPEED = 100;
  bool movingRight = false; bool movingLeft = false;

  sf::RectangleShape shape1(sf::Vector2f(500, 100));
  shape1.setFillColor(sf::Color::Green);
  shape1.setPosition(10, 20);


  sf::RectangleShape shape2(sf::Vector2f(500, 100));
  shape2.setFillColor(sf::Color::Red);
  shape2.setPosition(10, 125);

  const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

  sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while(wnd.isOpen()){

		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TimePerFrame){

			timeSinceLastUpdate -= TimePerFrame;

			// PROCESS INPUT
      sf::Event event;
    	while(wnd.pollEvent(event)){
        switch (event.type){
    			case sf::Event::KeyPressed:
    				if(event.key.code == sf::Keyboard::Left){
              movingLeft = true;
            }else if(event.key.code == sf::Keyboard::Right){
              movingRight = true;
            }
    				break;

    			case sf::Event::KeyReleased:
            if(event.key.code == sf::Keyboard::Left){
              movingLeft = false;
            }else if(event.key.code == sf::Keyboard::Right){
              movingRight = false;
            }
    				break;

    			case sf::Event::Closed:
    				wnd.close();
    				break;
    		}

    	}

      // UPDATE
      if(movingRight){ shape2.move(SPEED * dt.asSeconds(), 0.f); }
      if(movingLeft){ shape2.move(-SPEED * dt.asSeconds(), 0.f); }

		}

    // RENDER
    wnd.clear();
  	wnd.draw(shape1);
    wnd.draw(shape2);
    wnd.display();

	}

}
