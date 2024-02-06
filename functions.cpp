#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>

sf::Text InputText(std::string text, sf::Vector2f position, sf::Font& font) {
  sf::Text inputText;
  inputText.setFont(font);
  inputText.setFillColor(sf::Color::Red);
  inputText.setString(text);
  inputText.setPosition(position);
  return inputText;
}

float center(float window, float object) {
  return (window - object) / 2;
}

void loadIcon(sf::RenderWindow& window) {
  sf::Image icon;
  if (!icon.loadFromFile("assets/icon.jpg")) {
    std::cerr << "Failed to load icon\n";
  } else {
    std::cout << "Icon loaded successfully\n";
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  }
}

void loadFont(sf::Font& font) {
  if (!font.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "Failed to load font\n";
  } else {
    std::cout << "Font loaded successfully\n";
  }
}