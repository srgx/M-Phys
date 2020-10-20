#include <iostream>
#include <cassert>
#include <cmath>
#include "../Programs/arithmetic_functions.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

// g++ -c ex3.cpp ../Programs/arithmetic_functions.cpp
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

  const int P = 20; const int LENGTH = 900; const int WIDTH = 1e2;
  const int SCALE = 293; const int SHIFT = -15; const int CHAR_SIZE = 16;
  const auto FONT_COLOR = sf::Color::Black; const float SPEED = 70;

  sf::Font font; font.loadFromFile("Quesha-gndR.ttf");

  std::array<std::unique_ptr<sf::Text>,P> topLabs;
  std::array<std::unique_ptr<sf::Text>,P> botLabs;

  // Create Labels
  for(int i = 0; i<P; i++){

    const std::string S = std::to_string(i+1);
    const auto LOGV = log(i+1);

    // Top Slider
    topLabs.at(i) = std::make_unique<sf::Text>(S,font);
    topLabs.at(i)->setCharacterSize(CHAR_SIZE);
    topLabs.at(i)->setFillColor(FONT_COLOR);
    topLabs.at(i)->setPosition(LOGV*SCALE-SHIFT,97);

    // Bottom Slider
    botLabs.at(i) = std::make_unique<sf::Text>(S,font);
    botLabs.at(i)->setCharacterSize(CHAR_SIZE);
    botLabs.at(i)->setFillColor(FONT_COLOR);
    botLabs.at(i)->setPosition(LOGV*SCALE-SHIFT,125);

  }

  // Create window
  sf::RenderWindow wnd(sf::VideoMode(1024, 768), "Slider", sf::Style::Close);
  wnd.setFramerateLimit(30);

  bool movingRight = false; bool movingLeft = false;

  // Create top slider
  sf::RectangleShape shape1(sf::Vector2f(LENGTH, WIDTH));
  shape1.setFillColor(sf::Color::Green);
  shape1.setPosition(10, 20);

  // Create bottom slider
  sf::RectangleShape shape2(sf::Vector2f(LENGTH, WIDTH));
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

			// Process input
      sf::Event event;
    	while(wnd.pollEvent(event)){

        switch (event.type){

    			case sf::Event::KeyPressed:
    				if(event.key.code == sf::Keyboard::Left){
              movingLeft = true;
            }else if(event.key.code == sf::Keyboard::Right){
              movingRight = true;
            }else if(event.key.code == sf::Keyboard::Escape){
              wnd.close();
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

      // Update sliders and labels
      if(movingRight){
        shape2.move(SPEED * dt.asSeconds(), 0.f);
        for(auto i=botLabs.begin();i!=botLabs.end();i++){
          (*i)->move(SPEED * dt.asSeconds(), 0.f);
        }
      }

      if(movingLeft){
        shape2.move(-SPEED * dt.asSeconds(), 0.f);
        for(auto i=botLabs.begin();i!=botLabs.end();i++){
          (*i)->move(-SPEED * dt.asSeconds(), 0.f);
        }
      }

		}


    wnd.clear();

    // Render sliders
  	wnd.draw(shape1);
    wnd.draw(shape2);

    // Render labels
    for(auto i = 0;i<P;i++){
      wnd.draw(*topLabs.at(i));
      wnd.draw(*botLabs.at(i));
    }

    wnd.display();

	}

}
