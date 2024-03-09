#include <SFML/Graphics.hpp>
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

void didNotFindPath(sf::RenderWindow& window) {
  sf::Font font;
  loadFont(font);
  sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x * 0.8f, window.getSize().y * 0.8f));
  rectangle.setFillColor(sf::Color::Black);
  rectangle.setPosition(center(window.getSize().x, rectangle.getSize().x),
              center(window.getSize().y, rectangle.getSize().y));
  window.draw(rectangle);
  
  sf::Text text;
  text.setFont(font);
  text.setString("No path found");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Red);
  text.setPosition(center(window.getSize().x, text.getGlobalBounds().width),
                   center(window.getSize().y, text.getGlobalBounds().height));
  window.draw(text);
  window.display();
  sf::sleep(sf::seconds(2));
}