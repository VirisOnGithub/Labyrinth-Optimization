#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include "Case.h"

class Maze
{
private:
  std::vector<std::vector<Case>> maze;

public:
  Maze(int sizex, int sizey);
  ~Maze();
  void display() const;
  std::vector<Case> &operator[](int index);
  void breadthFirstSearch(int startingx,
                          int startingy,
                          int endingx,
                          int endingy,
                          int sizex,
                          int sizey);
  void depthFirstSearch(int startingx,
                        int startingy,
                        int endingx,
                        int endingy,
                        int sizex,
                        int sizey);
  void aStar(int startingx,
             int startingy,
             int endingx,
             int endingy,
             int sizex,
             int sizey);
  void setwallrandom(int startingx,
                     int startingy,
                     int endingx,
                     int endingy,
                     int sizex,
                     int sizey);
  void setwallnotrandom(int startingx,
                        int startingy,
                        int endingx,
                        int endingy,
                        int sizex,
                        int sizey);
  void drawPath(int x, int y);
  float distance(int x, int y, int endingx, int endingy);
};

#endif // MAZE_H
