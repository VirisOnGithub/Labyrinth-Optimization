#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

sf::Text InputText(std::string text, sf::Vector2f position, sf::Font& font) {
  sf::Text inputText;
  inputText.setFont(font);
  inputText.setFillColor(sf::Color::Red);
  inputText.setString(text);
  inputText.setPosition(position);
  return inputText;
}