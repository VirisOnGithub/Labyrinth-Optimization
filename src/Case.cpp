#include "Case.h"
#include <iostream>
#include <random>

Case::Case()
    : symbol('O'),
      visited(false),
      isWall(false),
      isStart(false),
      isEnd(false) {}

Case::~Case()
{
  parent = nullptr;
}

Case::Case(char symbol, bool visited, bool isWall, bool isStart, bool isEnd)
    : symbol(symbol),
      visited(visited),
      isWall(isWall),
      isStart(isStart),
      isEnd(isEnd) {}

char Case::getSymbol() const
{
  return symbol;
}

void Case::setSymbol(char symbol)
{
  this->symbol = symbol;
}

void Case::setStartCase()
{
  symbol = 'S';
  isStart = true;
}

bool Case::getStartCase() const
{
  return isStart;
}

void Case::setEndCase()
{
  if (isStart)
    std::cout << "Error: End case must be elsewhere than the start case."
              << std::endl;
  else
  {
    symbol = 'E';
    isEnd = true;
  }
}

bool Case::getEndCase() const
{
  return isEnd;
}

void Case::setWall()
{
  if (isStart || isEnd)
    std::cout
        << "Error: Wall case must be elsewhere than the start or end case."
        << std::endl;
  else
  {
    symbol = 'X';
    isWall = true;
  }
}

void Case::setVisited()
{
  if (isStart || isEnd || isWall)
    std::cout << "Error: Visited case must be elsewhere than the start, end or "
                 "wall case."
              << std::endl;
  else
  {
    visited = true;
  }
}

bool Case::getVisited() const
{
  return visited;
}

bool Case::getWall() const
{
  return isWall;
}

void Case::setDistance(float distance)
{
  this->distance = distance;
}

float Case::getDistance() const
{
  return distance;
}