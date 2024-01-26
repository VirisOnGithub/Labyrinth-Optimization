#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include "Case.h"

class Maze {
 private:
  std::vector<std::vector<Case>> maze;

 public:
  Maze(int sizex, int sizey);
  ~Maze();
  void display() const;
  std::vector<Case>& operator[](int index);
  void parcoursenlargeur(int startingx,
                         int startingy,
                         int endingx,
                         int endingy,
                         int sizex,
                         int sizey);
};

#endif  // MAZE_H
