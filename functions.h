#include <SFML/Graphics.hpp>

sf::Text InputText(std::string text, sf::Vector2f position, sf::Font& font);

float center(float window, float object);

void loadIcon(sf::RenderWindow& window);

void loadFont(sf::Font& font);

void didNotFindPath(sf::RenderWindow& window);