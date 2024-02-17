#include "Case.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>

Case::Case()
    : color(sf::Color::White),
      visited(false),
      isWall(false),
      isStart(false),
      isEnd(false) {}

Case::~Case() {
  parent = nullptr;
}

Case::Case(sf::Color color, bool visited, bool isWall, bool isStart, bool isEnd)
    : color(color),
      visited(visited),
      isWall(isWall),
      isStart(isStart),
      isEnd(isEnd) {}

sf::Color Case::getColor() const {
  return color;
}

void Case::setColor(sf::Color color) {
  this->color = color;
}

void Case::setStartCase() {
  if (isEnd)
    std::cout << "Error: Start case must be elsewhere than the end case."
              << std::endl;
  else {
    this->color = sf::Color::Red;
    isStart = true;
  }
}

void Case::setEndCase() {
  if (isStart)
    std::cout << "Error: End case must be elsewhere than the start case."
              << std::endl;
  else {
    this->color = sf::Color::Green;
    isEnd = true;
  }
}

void Case::setWall(bool wall) {
  if (isStart || isEnd)
    std::cout
        << "Error: Wall case must be elsewhere than the start or end case."
        << std::endl;
  else {
    this->color = sf::Color::Black;
    isWall = wall;
  }
}

void Case::setVisited(bool v) {
  if (isStart || isEnd || isWall)
    std::cout << "Error: Visited case must be elsewhere than the start, end or "
                 "wall case."
              << std::endl;
  else {
    visited = v;
  }
}

bool Case::getVisited() const {
  return visited;
}

bool Case::getWall() const {
  return isWall;
}

void Case::reset() {
  color = sf::Color::White;
  visited = false;
  isWall = false;
  isStart = false;
  isEnd = false;
  parent = nullptr;
}

void Case::partialReset(){
  if(!isWall && !isEnd & !isStart){
    reset();
  } else if (isEnd)
    parent = nullptr;
}