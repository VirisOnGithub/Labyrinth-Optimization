#include "Case.h"
#include <iostream>

Case::Case()
    : symbol('O'),
      visited(false),
      isWall(false),
      isStart(false),
      isEnd(false) {}

Case::~Case() {}

Case::Case(char symbol, bool visited, bool isWall, bool isStart, bool isEnd)
    : symbol(symbol),
      visited(visited),
      isWall(isWall),
      isStart(isStart),
      isEnd(isEnd) {}

char Case::getSymbol() const {
  return symbol;
}

void Case::setStartCase() {
  symbol = 'S';
  isStart = true;
}

void Case::setEndCase() {
  if (isStart)
    std::cout << "Error: End case must be elsewhere than the start case."
              << std::endl;
  else {
    symbol = 'E';
    isEnd = true;
  }
}

void Case::setWall() {
  if (isStart || isEnd)
    std::cout
        << "Error: Wall case must be elsewhere than the start or end case."
        << std::endl;
  else {
    symbol = 'X';
    isWall = true;
  }
}