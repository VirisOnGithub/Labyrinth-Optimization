#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Case.h"
#include "Maze.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
  sf::Event event;
  sf::Font font;
  sf::Text text;
  if (!font.loadFromFile("fonts/arial.ttf")) {
    std::cout << "Error loading font" << std::endl;
  }
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Red);
  text.setPosition(10, 10);
  text.setString("Hello world");
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
      }
    }
    window.clear();
    window.draw(text);
    window.display();
  }
}
