#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics/Color.hpp>


class Case {
 private:
  sf::Color color;
  bool visited;
  bool isWall;
  bool isStart;
  bool isEnd;

 public:
  Case* parent;
  Case();
  Case(sf::Color color,
       bool visited = false,
       bool isWall = false,
       bool isStart = false,
       bool isEnd = false);
  ~Case();
  sf::Color getColor() const;
  void setColor(sf::Color color);
  bool getVisited() const;
  void setStartCase();
  void setEndCase();
  void setWall();
  bool getWall() const;
  void setVisited();
};

#endif  // CASE_H
